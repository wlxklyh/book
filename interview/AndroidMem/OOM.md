
# 安卓OOM之分类

> 引用：https://tech.meituan.com/2019/11/14/crash-oom-probe-practice.html


----

OOM分类
- 堆内存分配失败
  - java堆内存溢出
  - 申请空间太大 无足够连续内存空间
- 创建线程失败
  - FD数量超出限制
  - 线程数量超出限制
  - 虚拟内存不足


异常：
Android 虚拟机最终抛出OutofMemoryError 的代码位于 /art/runtime/thread.cc
void Thread::ThrowOutofMemory msg
抛出异常的地方：
堆内存分配失败
系统源码文件：heap.cc


-----

## 一、堆内存分配失败
### 1、java堆内存溢出
对象分配内存时达到进程内存上限 Runtime.getRuntime.MaxMemory()
```java
void Heap::ThrowOutOfMemoryError(Thread* self, size_t byte_count, AllocatorType allocator_type)
抛出时的错误信息：
    oss << "Failed to allocate a " << byte_count << " byte allocation with " << total_bytes_free  << " free bytes and " << PrettySize(GetFreeMemoryUntilOOME()) << " until OOM";
```

### 2、申请空间太大 无足够连续内存空间 
没有足够大小的连续地址内存空间 这种一般是大量内存碎片导致  会比第一种多一段信息
```java
failed due to fragmentation (required continguous free “<< required_bytes << “ bytes for a new buffer where largest contiguous free ” << largest_continuous_free_pages << “ bytes)”; 其详细代码在art/runtime/gc/allocator/rosalloc.cc中，这里不作详述。
```
## 二、创建线程失败
系统源码在 thread.cc
```java
void Thread::CreateNativeThread(JNIEnv* env, jobject java_peer, size_t stack_size, bool is_daemon)
抛出时的错误信息：
    "Could not allocate JNI Env"
  或者
    StringPrintf("pthread_create (%s stack) failed: %s", PrettySize(stack_size).c_str(), strerror(pthread_create_result)));
```
这是创建线程时抛出的OOM异常
![20210112120611](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210112120611.png)


### 1、FD数量超出限制 
创建JNI失败 创建JNI两个步骤：
- 通过匿名共享内粗 分配4kb的内核态内存
- 通过linux的mmap调用映射到用户态虚拟内存地址空间

第一步创建匿名共享内存时，需要打开 ashmem文件 需要一个FD
```java
/art: ashmem_create_region failed for 'indirect ref table': Too many open files
 java.lang.OutOfMemoryError: Could not allocate JNI Env
   at java.lang.Thread.nativeCreate(Native Method)
   at java.lang.Thread.start(Thread.java:730)
```

下面则创建JNI时虚拟内存空间耗尽
```java
E/art: Failed anonymous mmap(0x0, 8192, 0x3, 0x2, 116, 0): Operation not permitted. See process maps in the log.
java.lang.OutOfMemoryError: Could not allocate JNI Env
  at java.lang.Thread.nativeCreate(Native Method)
  at java.lang.Thread.start(Thread.java:1063)
```
### 2、虚拟内存不足
```java
W/libc: pthread_create failed: couldn't allocate 1073152-bytes mapped space: Out of memory
W/tch.crowdsourc: Throwing OutOfMemoryError with VmSize  4191668 kB "pthread_create (1040KB stack) failed: Try again"
java.lang.OutOfMemoryError: pthread_create (1040KB stack) failed: Try again
        at java.lang.Thread.nativeCreate(Native Method)
        at java.lang.Thread.start(Thread.java:753)
```
### 3、线程数量超了
```java
W/libc: pthread_create failed: clone failed: Out of memory
W/art: Throwing OutOfMemoryError "pthread_create (1040KB stack) failed: Out of memory"
java.lang.OutOfMemoryError: pthread_create (1040KB stack) failed: Out of memory
  at java.lang.Thread.nativeCreate(Native Method)
  at java.lang.Thread.start(Thread.java:1078)
```

## 三、OOM问题定位
### 1、监控

#### 1.1、堆内存监控
怎么监控：堆内存超了关键还是要看之前分配了什么，使用hprof获取内存快照。
dump时机：1s钟判断一次：(runtime.getRuntime.totalMemory-free)/max > 80% 则dump 
分析时机：两种方法 一种是服务器分析 一种是客户端分析
线上分析：分析retainsize
线下分析：裁剪

#### 1.2、线程数量监控
华为 500 Thread.getAllStackTraces()

#### 1.3、FD监控
后台启动一个线程 每隔1s 读取一次当前进程创建FD数量 当FD数量到达阀值时 
```java
File fdFile=new File("/proc/" + Process.myPid() + "/fd");
File[] files = fdFile.listFiles();  
int length = files.length; //即进程中的fd数量
for (int i = 0; i < length ; i++) {
  if (Build.VERSION.SDK_INT >= 21) {
         Os.readlink(files[i].getAbsolutePath()); //得到软链接实际指向的文件
     } else {
      //6.0以下系统可以通过执行readlink命令去得到软连接实际指向文件，但是耗时较久
  }
}
```
用途：
- socket：网络
- anon_inode：handler thread
- 某个文件路径：文件

```java
FD信息：
anon_inode:[eventpoll]   count: 381
anon_inode:[eventfd]   count: 381
pipe   count  26
socket   count  32
/system/framework/framework-res.apk   count: 1
```

