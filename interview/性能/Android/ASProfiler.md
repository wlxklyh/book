# Profiler

##
|名称|方向|特点|要求|教程|
|-|-|-|-|-|
|1、systrace|查IO操作、CPU负载、Surface渲染、GC（系统调用）|额外消耗小、sample、看不到耗时、需要自己加sample、插桩|debuggable、Android4.0|python systrace/systrace.py|
|2、Android Profile|不能查启动过 比较耗时 查函数调用 查特定场景的耗时|用工具||
|3、LooperPrint||||


## systrace
[资料链接](https://zhuanlan.zhihu.com/p/142193191)

## LooperPrinter原理
Looper源码中的Logging 会在Loop开始用Logging输入>> 结束输出<< 
输出>>的时候用一个专门的线程加个定时任务获取线程堆栈 输出<<后取消这个定时任务 那么只有当超过XX时间输出<<才会打印堆栈