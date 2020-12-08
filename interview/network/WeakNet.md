#
## 总括
1、网络类型 网络信号判定弱网
2、ping公共DNS服务器判定弱网
3、
## 1、网络信号类型
1.0 监听广播
android.net.wifi.RSSI_CHANGED wifi信号强弱
android.net.conn.CONNECTIVITY_CHANGE 网络改变

1.1 判定是否有链接
ConnetivityManager getSystemService "connectivity"
netinfo = getActiveNetworkInfo()
netinfo.isAvailable() 
【弱网】无链接判定

1.2 wifi
netinfo.getType == 1 
updateWifiRssi
WifiManager.calculateSignalLevel() 传入等级范围 例如5 则划分成0-4等级 这个会记录1.5是前的

1.3 非wifi
2G：getsubtype 1 2 4 7 11 16【弱网】2G判定为弱网
3G：getsubtype 3 5 6 8 9 10 12 14 15 17 【弱网】3G判定为弱网
4G：getsubtype 13 18 19
5G：getsubtype 20
Unknown

1.4 记录网络切换  5000
列表记录时间戳和网络类型
hasNetSwitch 【弱网】如果在XX秒内切换了网络 会判定会弱网

1.5 网络信号 wifi是0-4 2以下为弱网
isWeakSignal 【弱网】

1.6 ？？
hasWeakLevelShown 【弱网】



## 2、网络通道 ping 两个公共DNS服务器
ping有有效周期 如果有效则使用上次结果
无效则起一个ping task 这个task 返回 探测错误码、packLossRatio、getFinalAvgRtt
1. ping target
this.targets.add(new IcmpTarget("119.29.29.29"));腾讯DNSPod 推出新公共DNS 服务：119.29.29.29
this.targets.add(new IcmpTarget("223.6.6.6"));
2. process Result

|网络类型|rtt|packloss|
|-|-|-|
|wifi|>200|15%|
|4G|>300|15%|
|5G|>200|15%|

|弱网类型|特征|
|-|-|
|1、全丢包|packLossRatio>=100% |
|2、高丢包高RTT |丢包率>15% 且 RTT>200（根据网络类型）|
|3、高丢包低RTT|丢包率>15% RTT<200（根据网络类型）|
|4、低丢包高RTT|丢包率<15% RTT>200（根据网络类型）|

## 3、单个ip的ping
 InetAddress.getByName 域名解析
PRC_CNL_DNS_UNKNOWN_HOST  UnknownHostException这个异常 则位置 弱网
PRC_CNL_DNS_FAIL 域名解析失败 弱网


## 4、NodeHandle
PRC_SDK_PROBE_DNS_FAIL
PRC_SDK_PROBE_IP_ILLEGAL
PRC_SCH_OVER_SEA
PRC_SCH_OVER_ISP
PRC_SCH_OVER_REGION
PRC_SCH_UNDEFINE_CODE

