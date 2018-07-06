#!/bin/sh
curTime=`date +%s`
nonce=${curTime}"123"
base="http://api.gpsspg.com/bss/?oid=159&bs=460,01,2531,6a88202&hex=16&type=&to=1&output=jsonp&callback=jQuery110207972865504789974"
outputPara=${base}"_"${nonce}"&_="$((${nonce}+1))
wget --referer="http://www.gpsspg.com/bs.htm"  --user-agent="Mozilla/5.0 (Windows NT 6.1; WOW64; rv:52.0) Gecko/20100101 Firefox/52.0" -O 1.json ${outputPara}
