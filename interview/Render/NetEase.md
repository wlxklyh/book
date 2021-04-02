一般都是我简历写啥了，就按什么问 按架构从上到下问的

引擎组织架构 ECS (entity - component-system)  https://www.zhihu.com/question/61169850/answer/185652605
引擎pipeline多pass ( 不透明渲染排序 - 半透明 - 后处理）  https://zhuanlan.zhihu.com/p/120185185
一些常用实现：描边实现  https://zhuanlan.zhihu.com/p/26409746
阴影实现 shadowMap等
MSAA https://zhuanlan.zhihu.com/p/32823370

中间就是有时候问图形的pipeline  vertexShader - 裁剪/归一化 - fragmentShader - depthTest - alpha Blend - alpha Test   (还有early-Z) 
https://zhuanlan.zhihu.com/p/136476068
再细就是vertexShader做什么， fragment渲染算法是什么，光照怎么写， pbr算法是什么 pbr https://zhuanlan.zhihu.com/p/53086060

下面硬件层就比较少问， 但是每个人都会问 怎么优化性能    cpu - 内存- 带宽-gpu https://zhuanlan.zhihu.com/p/26030252

还有移动端gpu  tile-based rendering 的架构  https://zhuanlan.zhihu.com/p/112120206


## 移动端 GPU概述

一、GPU渲染架构——TBR TBDR IMR

功耗->带宽->onchip memory SRAM 
test read write blend都在SRAM解决

