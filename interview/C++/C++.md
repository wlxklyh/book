# C++ 面试题


<!-- TOC -->

- [C++ 面试题](#c-面试题)
    - [游戏开发面试问题总结（一）——C++基础](#游戏开发面试问题总结一c基础)
- [define NULL 0](#define-null-0)

<!-- /TOC -->
摘自：https://mp.weixin.qq.com/s/55oPktz2VUFWAY5pVMju_w
## 游戏开发面试问题总结（一）——C++基础
1. 了解const吗？
const 就是定义一个 不会被修改的常量  可以修饰变量 引用 指针，可以用于函数、参数、成员函数修饰。使用const也可以减少程序出错，通常要注意的是区分常量指针 指针常量

2. reference和pointer的区别 哪些情况使用pointer
- 指针可以为空 引用不可以
- 指针可以不初始化 引用必须初始化 这也意味着引用不需要检测合法性
- 指针可以随时更改指向的目标 而引用初始化后就不可以再指向其他
特别的 重载[]的时候 使用引用

3. inline的优劣
优点：减少函数调用 so 会调用plt 还有计算偏移的消耗
缺点：增加函数体积 增加so大小 调试不方便 修改会增加编译时间 
有7种情况会拒绝 编译器拒绝内联

4. final 和 overrider
final:禁止继承该类或者覆盖该虚函数 
overrider:必须覆盖基类的匹配的虚函数  可以检查函数名字是否写错

5. C++03 98有什么不喜欢的用法 C++11有哪些喜欢的新特性
auto 一些迭代器或者map嵌套类型 auto写起来方便
vector 其他容器初始化 需要一个一个来
类成员初始值

#define NULL 0 
nullptr

有thread mutex
没有gc

6. delete数组的一部分 会发生什么 出现什么异常
delete[] 

7. 系统怎么知道越界
数组内存前后有 gap存4个 0xfd

8. C++编译器有哪些常见的优化

注意 static 变量不会被优化

9. mangling
指编译器给函数变量添加很多的描述信息到名称 用于传递更多信息 函数重载

10. 成员函数指针了解吗 可以转换void *吗
不可以 因为成员函数指针大小 并不是4字节 成员函数指针比较复杂
float (*fun)(XX,XX)

11. C++ 编译过程
预处理  编译  汇编（.s后缀的汇编代码） 汇编器 .o  链接 静态库 动态库

12. 静态库 和 动态库 


13. 内部链接 外部链接
内部 局部则内部链接 不会冲突
外部 

14. extern static
声明一个变量定义在其他文件

15. delegate 和 event区别
！！！

16. 使用过模版 有什么特性


17. 函数调用栈的变化！
栈帧：两个指针寄存器 ebp帧指针栈底 esp栈顶
调用其他函数的时候 就把参数押入栈顶 

18. 四种cast
const cast 去掉 const volatile

static cast 

dynamic cast 父到子 安全

reintercast

19. 设计模式
单例 
工厂
适配器
观察者

https://mp.weixin.qq.com/s/2dQw7tB9ec6B7fhmaGWSCg
游戏开发面试问题总结（二）——虚函数，内存，STL
1. 虚函数优缺点
优点：实现多态
缺点：
内存 每个类一个虚表 每个对象一个虚指针
执行效率 虚指针跳转

2. 多继承优缺点
优点：多个基类 特有功能
缺点：二义性

3. 为什么虚析构函数 没有虚构造
还没初始化虚指针

4. 内存布局

5. dynamic_cast 实现
RTTI 运行时 run time type identify
在虚函数的类的虚表的头部位置放RTTI的信息
！！！

6. 内存模型
堆 栈 自由存储区 全局静态 常量存储

7. 内存对齐


8. shared_ptr

malloc c函数
new C++的关键字

9. placement new意义
普通new 1、申请内存 返回指针 2、指定位置 构造函数 编译器做了这个
placement new的意义在于 在一块申请好的内存执行构造函数 
注意 如果此内存有对象 那么不会被析构

10. C++11 allocator
？？

11. RAII
resource acquisition is initialization 智能指针  lock

12. delete this 
delete 之后可以调函数不能调虚函数 成员变量

13. vector的增长
动态数组

14. map 有序和无序
红黑树：log n
哈希表：


15. stl里面的deque
分段连续 

16. stl heap priority_queue
heap 基于vector
priority 基于heap

17. 各个容器的数据结构
hashmap 哈希表
map 红黑树
优先队列 vector