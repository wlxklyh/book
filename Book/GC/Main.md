# 《垃圾回收的算法与实现》第1章学习GC之前

## 垃圾回收系列连载：

------
第 1 章 学习GC之前
第 2 章 GC标记-清除算法
第 3 章 引用计数法
第 4 章 GC复制算法
第 5 章 GC标记-压缩算法
第 6 章 保守式GC
第 7 章 分代垃圾回收
第 8 章 增量式垃圾回收
第 9 章 RC Immix 算法
第 10 章 Python 的垃圾回收
第 11 章 DalvikVM 的垃圾回收
第 12 章 Rubinius 的垃圾回收

[电子书下载链接](https://github.com/wlxklyh/book/blob/master/Book/GC/%E5%9E%83%E5%9C%BE%E5%9B%9E%E6%94%B6%E7%9A%84%E7%AE%97%E6%B3%95%E4%B8%8E%E5%AE%9E%E7%8E%B0---.pdf)

------

第 1 章 学习GC之前


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

