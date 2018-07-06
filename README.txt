本程序是封装基站查询网站的接口，来供其他程序调用
数据来源： http://www.gpsspg.com/bs.htm

参数说明
	MCC 移动设备国家代码 460 中国
	MNC 移动设备网络代码 00移动 01联通 11电信4G
	LAC / TAC 1~65535
	CI 2G(1~65535) 3G/4G(1~268435455)

如何显示手机基站编号信息
	安卓系统： 拨号*#*#4636#*#*进入手机信息工程模式后查看。

	iPhone：拨号*3001#12345#*进入FieldTest，LAC(MM Info > Serving PLMN)，3G cellid(UMTS Cell Environment > UMTS RR Info)，2G cellid(GSM Cell Environment > GSM Cell Info > GSM Serving Cell)

	WP系统: 拔号##634#(Lumia/三星)或##3282#(HTC)进入工程模式后查看。仅有部份手机有效。
