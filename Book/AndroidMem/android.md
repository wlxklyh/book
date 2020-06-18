# 安卓内存优化

## 一、安卓内存管理基础
1. paging + mmap:page 不在物理内存上的原因有，backup file或者从未分配过
2. swap zram:swap是会把物理内存备份到backup file上 安卓大多数情况没有 IO代价大 有一种情况例外 只读的dex so文件 换出不用写 只用读
zram是压缩物理内存的page
3. MMap函数 可执行 可读 可写 不可存取
backup file的读取映射方式？
4. new malloc

## 二、安卓程序的内存构成
adb shell dumpsys meminfo xxx.xxx.xxx

1、内存衡量分类
proportional set size包括了跟其他进程的共享内存 字体
private dirty private clean完全是进程自己占用的物理内存 clean是可能被swap的内存部分 例如so库文件 dirty是不能被swap的内存 dirty是需要优化的

swapped dirty不是swap-out的内存 而是被压缩调的private dirty内存

pss包括了private dirty和private clean 最终评判标准是pss+swapped dirty

2、内存类别
1. Native heap:这是C/C++层直接通过malloc分配的内存 UE的框架中你几乎不会走这部分内存  因为统一走了FMalloc  所以Native Heap大可能是第三方库  和 gles的driver在client内存一侧的分配

2. Dalvik Heap/Other 这是安卓java虚拟机分配的内存 也就是java的内存

3. Stack:栈内存

4. Ashmem Anonymous shared memory 通常不会很大 和 操作系统有关 进程共享内存

5. GFX dev:显存 安卓显存和内存在同样的物理设备上面 总内存是包括显存  texture buffer shader programe

6. Other Dev:除了显卡之外的其他设备mmap后的物理内存 声卡

7. .so mmap 这个就是so库本身文件占用的物理内存 会根据游戏进程缺页就读进来  有机会被swap-out

8. apk dex oat art mmap都是程序本身mmap占用的内存

9. other mmap 

10. Unknown：UE程序最大的一块 meminf 

3、RSS VSS
adb shell top 可以看到 rss vss
resident set size 物理内存

4、vss虚拟空间大小

5、adb run -as xxx.xxx.xxx cat /proc/pid/smaps


## 三、UE程序完整内存组成
