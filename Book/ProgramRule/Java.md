#
## 1、基本原则
- 不要格式化不在当前范围的代码

## 2、基础
- 文件：用最顶层类名来命名文件 utf8 2000行
- 字符：tab = 4空格
- 垃圾清理：清楚无用的注释 方法 变量 类 配置文件
- package语句：不使用通配符 不换行  静态导入和非静态导入分割
- 类：重载方法不应该分割开
- 大括号：必须使用大括号 换行规则如下
```
if (condition()) {
} else if (otherCondition()) {
}
```
- 块缩进：4个空格
- 一行最多一个语句
- 行长度：120 
- 长行断行：
```
StringBuffer sb = new StringBuffer();
// 超过100个字符的情况下，换行缩进8个空格，点号和方法名称一起换行
sb.append("zi").append("xin")...
        .append("huang")...
        .append("huang")...
        .append("huang");
```
- 空行：很多规则
- L:long max = Math.max(1L, 5L)
- 16进制：大写
- 数字的前缀、后缀必须小写：float f = 1.0f; 不能是F
- 不要使用组合声明，比如int a, b;
- 数组 new int[]{1, 2}
- switch语句：default必须存在
- /* ... */
- 包名：全部小写
- 简化容器模版申明：Map<String, Map<String, Object>> map = new HashMap<>();
- 删除容器中的元素：
```
Iterator<String> iterator = list.iterator();
while (iterator.hasNext()) {
    String item = iterator.next();
    if (删除元素的条件) {
        iterator.remove();
    }
}
```