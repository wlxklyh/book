# 关于Gama空间的bug

## bug
|光照强度系数|bug fix前|bug fix后|
|-|-|-|
|0.01|![20210525174143](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525174143.png)|![20210525221041](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525221041.png)|
|0.02|![20210525174344](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525174344.png)|![20210525221303](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525221303.png)|
|0.03|![20210525174423](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525174423.png)|![20210525221412](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525221412.png)|
|0.04|![20210525174500](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525174500.png)|![20210525223249](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525223249.png)|
|0.05|![20210525174549](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525174549.png)|![20210525223451](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525223451.png)|
|0.1|![20210525174641](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525174641.png)|![20210525175708](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20210525175708.png)|

看到上面的图，bug fix前发现修改参数不是线性的，所以要想到去查下是在gama空间还是线性空间做的加强。

## bug修复前后的代码
Fix前
```cpp
color = srgb_to_linear(al.color * lightFactor)) if lightGamma else al.color * lightFactor) //lightFactor就是0.01这些参数
```

Fix后
```cpp
color = (srgb_to_linear(al.color) if lightGamma else al.color) * lightFactor)//lightFactor就是0.01这些参数
```



## 线性空间 Gama空间的说明
有这三种空间的原因是 CRT显示器显示图像的时候做了伽马值为2.2的纠正（2.2 次幂） 之后的LCD显示器为了兼容性也做了同样的纠正（2.2 次幂），2.2是0.45的倒数 互相抵消得到了与原始图像一直的图像（color ^ 0.45 ^ 2.2 = color ^ 1）所以绝大多数的图片都是做了0.45次幂的校正过的 等显示的时候会2.2次幂回去。

回到这个bug，
**Fix前：**
(color * 0.01) ^ 2.2 =  0.01 ^ 2.2 * color ^ 2.2
**Fix后是：**
(color) ^ 2.2 * 0.01 = 0.01 * color ^ 2.2

所以0.01 ^ 2.2远远小于0.01 所以看到Fix前是**很暗的**，而且是**非线性变亮的**。

## 对游戏开发的影响
pbr的计算都是在线性空间计算，所以如果美术出图是在0.45gama空间，要先通过2.2次幂转化到线性空间 在做计算，然后计算完再转回sRGB（0.45gama空间），然后显示器显示的时候 会做2.2次幂的计算去显示线性空间的颜色。
所以**特别注意基本上计算都在线性空间，在制定工作流的时候要看下美术的图是在什么空间的sRGB还是线性空间**