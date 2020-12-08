
# 录屏

## Demo
MediaCodec
https://blog.csdn.net/junzia/article/details/78154648

demo
https://github.com/wzystal/MediaRecorder

MediaCodec录制
https://github.com/ChinaZeng/SurfaceRecodeDemo


## 录屏坑
https://www.jianshu.com/p/f8570c896ca8

那我们是不是直接吧TextureView的SurfaceTexture创建的Surface传给MediaRecorder让它捕捉TextureView的内容就行了呢?
可惜的是如果直接用MediaRecorder.setInputSurface将Surface设置进去,会抛出异常:
09-22 14:53:47.473   897   943 E AndroidRuntime: java.lang.IllegalArgumentException: not a PersistentSurface
09-22 14:53:47.473   897   943 E AndroidRuntime:        at android.media.MediaRecorder.setInputSurface(MediaRecorder.java:165)
