https://github.com/JoeyDeVries/LearnOpenGL


## 引擎组织架构 ECS (entity - component-system)  https://www.zhihu.com/question/61169850/answer/185652605
Entity：代表游戏中的实体 是component的容器
Component：实体中有什么 一个或多个Component组成了游戏中的逻辑实体 只有数据  不涉及逻辑
System:对Componet集中进行逻辑处理

优点：
模式简单
概念统一
结构清晰
容易组合 高度复用
扩展性强

Unity是未脱离OOP的Entity Component模式


引擎pipeline多pass ( 不透明渲染排序 - 半透明 - 后处理）  https://zhuanlan.zhihu.com/p/120185185


一些常用实现：描边实现  https://zhuanlan.zhihu.com/p/26409746


阴影实现 shadowMap等

MSAA https://zhuanlan.zhihu.com/p/32823370

中间就是有时候问图形的pipeline  vertexShader - 裁剪/归一化 - fragmentShader - depthTest - alpha Blend - alpha Test   (还有early-Z) 


https://zhuanlan.zhihu.com/p/136476068


再细就是vertexShader做什么， fragment渲染算法是什么，光照怎么写， pbr算法是什么 pbr https://zhuanlan.zhihu.com/p/53086060


下面硬件层就比较少问， 但是每个人都会问 怎么优化性能    cpu - 内存- 带宽-gpu https://zhuanlan.zhihu.com/p/26030252


## 还有移动端gpu  tile-based rendering 的架构  https://zhuanlan.zhihu.com/p/112120206
1、


