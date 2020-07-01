# 设计模式

## 零、六大原则
总原则 开闭原则：对扩展开发，对修改封闭
1、单一职责原则：每个类应该实现单一的职责 不然就应该分开
2、里氏替换原则：任何基类出现的地方 子类都可以出现 子类对父类的方法尽量不要重写和重载。
3、依赖倒转原则：面向接口编程 依赖抽象不依赖具体  例子 Driver类里面的car 后面可能是bus 应该抽象成一个抽象类交通工具
4、接口隔离原则：尽量使用多个专门的接口  不是建立一个臃肿庞大的接口 接口的颗粒度小
5、迪米特法则：最小知道原则 对要调用要耦合的类知道最小 友元类来传达  会有一个大的中介类 解耦
6、合成复用原则：尽量使用合成 、 聚合 而不是使用继承

## 一、设计模式

### 1、工厂模式 
生产产品

### 2、抽象工厂 
生产工厂

### 3、单例模式 

### 4、建造模式 
Builder 例如 Actor的创建 会组装component 用Builder

### 5、原型模式
对象池模式  prefab池  Cache模式
资源优化场景 
### 6、适配器模式
iOS 和 Android原生调用的 适配器

### 7、桥接模式 ？？
抽象和实现解耦 把DrawApi抽象 把RedCircle 的draw分别实现 然后放到Circle里面

### 8、过滤器模式
List<Person> persons
Criteria male;
Criteria female;
Criteria singleMale;
male.meetCriteria(persons)
female.meetCriteria(persons)
singleMale.meetCriteria(persons)



### 9、组合模式
部分-整体  例子：目录树就可以用这个模式
File->BaseClass Folder->BaseClass



### 10、装饰模式
wrapper模式 不修改原有的类 进行扩展 例如Form里面装入了 LuaForm

### 8、命令模式
执行class 成员List 收集Command然后update里面去执行
主要解决请求者和行为实现的紧耦合的关系，某些场合要对行为进行记录、撤销、重做  紧耦合的设计不适合。优点降低了耦合，新命令容易添加进去。


### 9、解释器模式
文法语法解释器 SQL等语言解释里面

### 10、迭代器模式
一个是容器Container  getIterator 
一个是Iterator 迭代器  接口有GetNext HasNext

### 11、观察者模式
观察者Observer 被观察着Subject要存一个List<Observer> 被观察者被改变了 通知所有观察者

### 12、中介者模式

