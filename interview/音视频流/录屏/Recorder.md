
# 录屏

## 相机拍摄加后处理效果录制
MediaCodec
https://blog.csdn.net/junzia/article/details/78154648

demo
https://github.com/wzystal/MediaRecorder

MediaCodec录制
https://github.com/ChinaZeng/SurfaceRecodeDemo
## 谷歌demo

### 1、视频录制的psnr


### 
https://www.jianshu.com/p/f8570c896ca8

那我们是不是直接吧TextureView的SurfaceTexture创建的Surface传给MediaRecorder让它捕捉TextureView的内容就行了呢?
可惜的是如果直接用MediaRecorder.setInputSurface将Surface设置进去,会抛出异常:
09-22 14:53:47.473   897   943 E AndroidRuntime: java.lang.IllegalArgumentException: not a PersistentSurface
09-22 14:53:47.473   897   943 E AndroidRuntime:        at android.media.MediaRecorder.setInputSurface(MediaRecorder.java:165)

作者：嘉伟咯
链接：https://www.jianshu.com/p/f8570c896ca8
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。