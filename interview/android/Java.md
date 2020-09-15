# Java

## android双亲委托
- ClassLoader 加载class 提供给程序运行时使用
加载过程
1. 源ClassLoader先判断这个Class是否加载过 加载过则返回 如果没有则委托给父类加载器
2. 依此类推 直到祖先类加载器  如果也没有加载过  那么从对应的类路径下寻找class字节码文件 加载成功返回class 失败委托给始祖类加载器的子类加载器

