## 全屏图适配

```
//--------------------------------------------------
/// 下面的函数的方案如下 【四周裁剪】
/// 原图：          iphonex     ipad         iphone6
/// +-+-----+-+   +-------+
/// | |     | |   |       |
/// +-+-----+-+   |       | +---------+    +------+
/// | |     | |   |       | |         |    |      |
/// | |     | |   |       | |         |    |      |
/// | |     | |   |       | |         |    |      |
/// | |     | |   |       | |         |    |      |
/// +-+-----+-+   |       | +---------+    +------+
/// | |     | |   |       |
/// +-+-----+-+   +-------+
/// 768 x 1248   576 x 1248   768 x 1024  576 x 1024
/// [注]：可以是768 x 1248的等比例放大
//--------------------------------------------------
private static float DesignPicOriWidth = 768;   //美术出图宽
private static float DesignPicOriHeight = 1248; //美术出图高
private static float DesignPicBestWidth = 576;   //iphone6宽
private static float DesignPicBestHeight = 1024; //iphone6高

//--------------------------------------------------
/// 也可以是768 x 1248的比例  如果是更大的分辨率可以更清晰
//--------------------------------------------------
public static Rect GetTailorAdapterRect(float PicOriWidth,float PicOriHeight)
{
    //得到在这个图分辨率下的最佳宽高
    float PicBestWidth = DesignPicBestWidth / DesignPicOriWidth * PicOriWidth;
    float PicBestHeight = DesignPicBestHeight / DesignPicOriHeight * PicOriHeight;


    //原图左上角是（0,0） 计算可视区域
    Rect TailorAdapterRect = new Rect(0, 0, PicOriWidth, PicOriHeight);
    float realWidth = PicOriWidth;
    float realHeight = PicOriHeight;
    float realPosx = 0;
    float realPosy = 0;

    float  defaultW = UIHelper.GetDefaultScreenWidth();
    float  defaultH = UIHelper.GetDefaultScreenHeight();
    float aspectRatioDevice = defaultH * 1.0f / defaultW;
    float aspectRatioIphone6 = PicBestHeight * 1.0f / PicBestWidth ;

    //（1）更加高一些：例如iphonex
    if (aspectRatioDevice > aspectRatioIphone6)
    {
        //高宽
        realHeight = PicBestWidth * aspectRatioDevice;
        realWidth = PicBestWidth;
    
    }
    //（2）更加宽一些：例如ipad
    else
    {
        //高宽
        realHeight = PicBestHeight;
        realWidth = realHeight/aspectRatioDevice;
    }
    //坐标
    realPosx = (PicOriWidth - realWidth) / 2;;
    realPosy = (PicOriHeight - realHeight) / 2;;

    TailorAdapterRect.x = realPosx;
    TailorAdapterRect.y = realPosy;
    TailorAdapterRect.width = realWidth;
    TailorAdapterRect.height = realHeight;

    return TailorAdapterRect;
}
```