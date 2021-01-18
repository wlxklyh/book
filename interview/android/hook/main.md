# Hook

## 加载so
JNI_OnLoad JNI_OnUnLoad
当执行system_loadlibrary的时候 会执行这个so的JNI_OnLoad 如果没有这个函数 默认使用jni 1.1版本


## xhook xhook_register
int xhook_register(const char *pathname_regex_str, const char *symbol,
                   void *new_func, void **old_func)
1、so路径
2、符号名字
3、新函数 
4、旧函数