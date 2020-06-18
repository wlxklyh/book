## Crunch

## 包量
||ETC2|Crunch Etc2|Jpg|
| -- | --|--|--|
|打进bundle的大小|100M|31M|56M|
|内存|一样|一样|一样|
|效果||aov说效果不好|他们用jpg运行时压成etc|

建议：
可以在CDN图上试下


1、磁盘：使用crunch包量会是ETC的31% （Bundle ChunkBase compress）
2、内存：一样
3、性能：没测，运行时会解压crunch纹理成ETC再上传GPU
4、效果：AOV说效果不是那么好， 他们用Jpg运行时压缩成ETC 这个差

建议：
1、在icon图 和 CDN图里面使用下crunch  这个要找unity拿patch?
2、如果crunch效果不好 可以试下AOV的jpg的方案来减包量 

