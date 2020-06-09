# 垃圾回收算法

gc简单介绍过程
https://www.cnblogs.com/qianguyihao/p/4744233.html
1、引用计数  循环引用问题
2、垃圾回收
2.1 标记清除： 程序暂停 且有内存碎片
2.2 复制算法（新生代）： 两块内存  开始使用第一块 垃圾回收就复制过去 解决了内存碎片 节省了清除的过程时间 内存翻倍
实际是Eden 和 两个 survivor来处理 实在不够大对象也会往老年代送
2.3 标记整理（老年代）：
G1用的是Recommend set
CSM回收器用的是 卡槽标记




apk 安装过程
https://cloud.tencent.com/developer/article/1199458
## 2 GC标记-清除算法




## 3 项目

