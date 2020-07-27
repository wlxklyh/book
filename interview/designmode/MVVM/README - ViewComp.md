## 对比拆Form和拆ViewComp

层级限制也就限制了Form这种拆法  只能拆层级最高的

|方案|Form|ViewComp|
|--|--|--|
|层级|局限的层级|**主Form里面控制层级**|
|生命周期|自己管理|**框架管理**|
|通信|事件，逻辑单元分开|**Form可以访问ViewComp**|
|复用|位置固定大小固定|**更好复用**|
|排期|**更快直接就可以**|需要建设框架|


弊端：
1、需要程序去处理