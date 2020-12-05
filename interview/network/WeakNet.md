#

## 网络信号类型
1. 监听广播
1、android.net.wifi.RSSI_CHANGED wifi信号强弱
2、android.net.conn.CONNECTIVITY_CHANGE 网络改变
2. 记录信号和网络类型
3. 记录网络切换
4. 记录信号
5. 推断
根据以上可以得出弱网类型
PRC_SIG_DISCONNECTED 无链接
PRC_SIG_2G 2G
PRC_SIG_3G 3G
PRC_SIG_AP_SWITCH 网络切换 5000 切换时间
PRC_SIG_SIGNAL_WEAK 网络信号弱 2 


## 网络通道 ping 两个公共DNS服务器
ping有有效周期 如果有效则使用上次结果
无效则起一个ping task 这个task 返回 探测错误码、packLossRatio、getFinalAvgRtt
1. ping target
this.targets.add(new IcmpTarget("119.29.29.29"));腾讯DNSPod 推出新公共DNS 服务：119.29.29.29
this.targets.add(new IcmpTarget("223.6.6.6"));
2. process Result
丢包配置
wifi >15% hight rtt>200 packLossDiff 1 rttdiff 50
4G >15% hight rtt>300 5 100
5G >15% hight rtt>200 1 50
PRC_CNL_ALL_PACK_LOSS 全丢包 packLossRatio>100%   
PRC_CNL_HIGH_LOSS_HIGH_RTT 高丢包高RTT 丢包率大于15% 且 RTT大于200
PRC_CNL_HIGH_LOSS_LOW_RTT  高丢包低RTT  
PRC_CNL_LOW_LOSS_HIGH_RTT  低丢包高RTT  
PRC_SDK_PING_RTT_LOST 丢ping

## 单个ip的ping
 InetAddress.getByName 域名解析
PRC_CNL_DNS_UNKNOWN_HOST  UnknownHostException这个异常 则位置 弱网
PRC_CNL_DNS_FAIL 域名解析失败 弱网


## NodeHandle
PRC_SDK_PROBE_DNS_FAIL
PRC_SDK_PROBE_IP_ILLEGAL
PRC_SCH_OVER_SEA
PRC_SCH_OVER_ISP
PRC_SCH_OVER_REGION
PRC_SCH_UNDEFINE_CODE

