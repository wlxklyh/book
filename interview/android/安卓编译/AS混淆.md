# Android Studio如何混淆

## 为什么要混淆
了解安卓程序编译的会知道 其实我们的apk并不是很安全，从apk从可以解包出，步骤：
1. 将apk文件改成zip结尾 然后解压zip 然后就会发现里面有一个classes.dex

2. dex2jar 这个工具将dex文件转成jar
下载地址：http://sourceforge.net/projects/dex2jar/files/
用这个工具的命令 转jar
```cpp
d2j-dex2jar classes.dex
```
3. jd-gui 这个工具用于将jar转成java代码
下载地址：http://jd.benow.ca/
用这个工具打开classes-dex2jar.jar
![20201028220024](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20201028220024.png)

**因此最简单的就是把java混淆了，让别人看不懂**

## AS里面配置混淆
### 配置混淆
在build.gradle里面配置
```cpp
release {
    minifyEnabled true //用于设置是否启用混淆 
    proguardFiles getDefaultProguardFile('proguard-android.txt'), 'proguard-rules.pro'
}
```

打包后解出来的jar：
![20201028221119](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20201028221119.png)

![20201028221154](https://raw.githubusercontent.com/wlxklyh/imagebed/master/imageforvscode/20201028221154.png)

### 配置混淆规则
```cpp
-dontusemixedcaseclassnames 表示混淆时不使用大小写混合类名。

-dontskipnonpubliclibraryclasses 表示不跳过library中的非public的类。

-verbose 表示打印混淆的详细信息。

-dontoptimize 表示不进行优化，建议使用此选项，因为根据proguard-android-optimize.txt中的描述，优化可能会造成一些潜在风险，不能保证在所有版本的Dalvik上都正常运行。

-dontpreverify 表示不进行预校验。这个预校验是作用在Java平台上的，Android平台上不需要这项功能，去掉之后还可以加快混淆速度。

-keepattributes *Annotation* 表示对注解中的参数进行保留。


-keep public class com.google.vending.licensing.ILicensingService
-keep public class com.android.vending.licensing.ILicensingService
上面两行表示不混淆上述两个类

-keep class com.tencent.wns.config.ConfigManager {*;}
上面一行表示不混淆这整个类
```