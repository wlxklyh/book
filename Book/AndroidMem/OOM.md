
# OOM 
https://tech.meituan.com/2019/11/14/crash-oom-probe-practice.html

## 
OOM分类
- java堆内存溢出
- 无足够连续内存空间
- FD数量超出限制
- 线程数量超出限制
- 虚拟内存不足


### 1. 堆内存分配失败 

#### 1.1 对象分配内存时达到进程内存上限 Runtime.getRuntime.MaxMemory()
#### 1.2 没有足够大小的连续地址空间  大量的内存碎片导致

### 2. 创建线程失败
#### 2.1 创建JNIEnv结构体
步骤1:通过安卓的匿名共享内存 分配4kb 内核态内存
步骤2:通过linux的mmap调用映射到用户态虚拟内存地址空间


#### 2.2 创建线程失败