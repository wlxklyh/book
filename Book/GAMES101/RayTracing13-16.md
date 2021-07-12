# Ray Tracing

## 13  

Ray Casting
1. Generate an image by casting one way per pixel
2. Check for shadows by sending a ray to the light
知乎的解释：https://zhuanlan.zhihu.com/p/72673165
分为eye ray 和 Shadow ray，如果eye ray跟场景有交点 交点进行着色 如果交点跟光没有交点则用设定的背景颜色 如果有交点则做计算。

whitted-style ray tracing
1. 遇到镜面则反射 遇到折射的则折射 遇到漫反射的就停止递归。
2. 
问题：
1. 因为说完全镜面反射 所以看起来很假 没有那种部分镜面反射的
2. 遇到漫反射就停止了 实际应该继续追踪的

后面的BVH 这些先忽略

## 14  



## 15  

## 16  

