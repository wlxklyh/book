# 

## 目录相关
- UE4 Source目录  
    - Developer 主要是跨平台 merge和一些底层工具  
    - Editor 主要是编辑器相关代码  
    - Programs 主要是独立于引擎 但大多数又依赖引擎的工具 UBT在这里  
    - ThirdParty 第三方库或者插件  

- UE4 Runtime里面的模块  
    - Launch 模块 
    各个平台的main函数入口   
    -   

## 编译相关  
- PCH预编译头    

- 怎么避免include巨大的header file  
include巨大的头文件有什么危害？？
方法：
```cpp
#include "Misc/MonolithicHeaderBoilerplate.h"
MONOLITHIC_HEADER_BOILERPLATE()
//下面解释下这两句
1. 首先看下头文件MonolithicHeaderBoilerplate.h：
#if UE_IS_ENGINE_MODULE && !defined(SUPPRESS_MONOLITHIC_HEADER_WARNINGS)
	#define MONOLITHIC_HEADER_BOILERPLATE() COMPILE_WARNING("Monolithic headers should not be used by this module. Please change it to explicitly include the headers it needs.")
	#define SUPPRESS_MONOLITHIC_HEADER_WARNINGS 1
#else
	#undef MONOLITHIC_HEADER_BOILERPLATE
	#define MONOLITHIC_HEADER_BOILERPLATE()
#endif

2. 如果当前模块定义了UE_IS_ENGINE_MODULE 或者没有warning过则MONOLITHIC_HEADER_BOILERPLATE会报错

3. UE_IS_ENGINE_MODULE则在UBT里面定义
if (Rules.bTreatAsEngineModule)//这里得看 build.cs文件
{
    CompileEnvironment.Definitions.Add("UE_IS_ENGINE_MODULE=1");
}
这里没细看 应该大部分模块都是有这个定义

```
### Build.cs



## C++

## 技巧

mklink /J E:\ue_4.25\Engine\Intermediate C:\UEBuild\Intermediate 
mklink /J E:\ue_4.25\Engine\Source C:\UEBuild\Source


