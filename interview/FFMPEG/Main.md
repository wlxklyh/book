# FFmpeg

## 知识搜索
总的：https://blog.csdn.net/leixiaohua1020/article/details/15811977

基础：https://blog.csdn.net/leixiaohua1020/article/details/18893769

## 互联网视频文件
### 解协议
网络传播用的是流媒体协议 HTTP RTMP MMS 解析为标准的相应的封装格式数据
### 解封装
分离成音频流压缩编码数据 和 视频流压缩编码数据 例如FLV解封装为H.264编码的视频码流 和 AAC编码的音频码流
### 解码音视频
解码为非压缩的视频、音频原始数据 音频的压缩编码标准包含  AAC  MP3  AC-3等  视频的压缩编码标准有H.264 MPEG2  VC-1  
压缩编码的视频数据输出成非压缩的颜色数据  YUV420p  RGB 
### 音视频同步
同步解码出来的视频和音频数据 并将视频 音频数据送至 显卡和声卡
