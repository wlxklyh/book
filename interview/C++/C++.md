# 

## 1. 四种cast
```cpp
//1. c风格的cast
(T)expression;
//2. 基础类型转换 有继承关系的类的转换（但是有安全问题） 这个会做编译检查 
static_cast<T>(expression);
//3. 转换的类必须要有虚函数 因为是根据虚函数表来做动态检查的
dynamic_cast<T>(expression);
//4. 把指针转换成整数  0x00b4cd10 -> 11848976
reinterpret_cast<T>(expression);
char *p = "This is a example.";
int i = reinterpret_cast<int>(p); 
//5. 其中T必须为指针或引用 。
//主要是用来去掉const属性，当然也可以加上const属性。主要是用前者，后者很少用。
const_cast<T>(expression);
const int i = 3;
int* p = const_cast<int*>(&i);
*p = 10;        
//原因：读取const a的值的汇编代码，它不是从内存取数据出来，而是直接得到常数0xa
```
