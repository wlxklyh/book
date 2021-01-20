# Profiler

##
|名称|方向|特点|要求|教程|
|-|-|-|-|-|
|1、systrace|查IO操作、CPU负载、Surface渲染、GC（系统调用）|额外消耗小、sample、看不到耗时、需要自己加sample、插桩|debuggable、Android4.0|python systrace/systrace.py|
|2、Android Profile|不能查启动过 比较耗时 查函数调用 查特定场景的耗时|用工具||
|3、LooperPrint||||


## systrace
[资料链接](https://zhuanlan.zhihu.com/p/142193191)

## LooperPrinter原理
Looper源码中的Logging 会在Loop开始用Logging输入>> 结束输出<< 
输出>>的时候用一个专门的线程加个定时任务获取线程堆栈 输出<<后取消这个定时任务 那么只有当超过XX时间输出<<才会打印堆栈
ß

## 内存加压力
```java

 List<Bitmap> bitmapList = new ArrayList<>();
    BroadcastReceiver receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Logger.i(TAG, "onReceive");

            ThreadUtil.getInstance().post(new Runnable() {
                @Override
                public void run() {
                    Bitmap bitmap  = BitmapFactory.decodeResource(getResources(), R.drawable.splash_bg_top_1080_1920);
                    if (bitmap == null) {
                        Logger.i(TAG, "onReceive bitmap return");
                        return;
                    }

                    for(int i = 0; i < Integer.MAX_VALUE; i++) {
                        Bitmap cp = bitmap.copy(Config.ARGB_8888, false);
                        if (cp == null) {
                            try {
                                Thread.sleep(100);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                        bitmapList.add(cp);

                        Logger.i(TAG, "onReceive bitmap list index:"+i+", cp:"+cp);
                    }
                }
            });
        }
    };



IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("com.water.test");
        getActivity().registerReceiver(receiver, intentFilter);




adb shell am broadcast -a "com.water.test"



new Thread(){
@Override
public void run() {
    try {
        long memory = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        long maxMemory = 87 * Runtime.getRuntime().maxMemory() / 100;
        while (memory <= maxMemory){
            memory = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
            Object object[] = new Object[1024 * 100];
            objects.add(object);
            Thread.sleep(20);
            handler.obtainMessage(0, memory).sendToTarget();
        }
        isCelling = false;
    } catch (InterruptedException e) {
        e.printStackTrace();
    }
}
}.start();

```

