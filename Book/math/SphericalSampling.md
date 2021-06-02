# 球面采样
https://000ddd00dd0d.github.io/2019/04/07/Spherical-Sampling/
http://corysimon.github.io/articles/uniformdistn-on-sphere/

## 1、轴向均匀采样
```cpp
do
{
    x = uniform(-1, 1);//uniform是均匀采样
    y = uniform(-1, 1);
    z = uniform(-1, 1);
}while((x,y,z) == (0,0,0));
return normalize((x,y,z));
```
## 2、轴向正态采样
```cpp
do
{
    x = normal(-1, 1)//normal是正态采样
    y = normal(-1, 1)
    z = normal(-1, 1)
}while((x,y,z) == (0,0,0))
return normalize((x,y,z))

```

## 3、Marsaglia采样

```cpp
do
{
    u = uniform(-1, 1);
    v = uniform(-1, 1);
    r2 = u^2 + v^2;
}while(r2 > 1);
x = 2 * u * sqrt(1 - r2);
y = 2 * v * sqrt(1 - r2);
z = 1 - 2 * r2;
return (x, y, z);
```