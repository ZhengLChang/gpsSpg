#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


int getGpsSpg(int mcc, int mnc, int lac_tac, int ci, char *getDataStr,
		int getDataStrSize);
int main(void)
{
	char getDataStr[1024] = "";
/*
Warning:
致命的数据错误返回格式（伪装成正确的数据），获得这种数据会被欺骗
{"status":200,"msg":"ok","count":1,"result":[{"id":"460-001-09521-111706626","lat":"63.5816583324","lng":"175.8781693333","radius":"1500","address":"北京市朝阳区望京街道方恒购物中心8952","roads":"望京小街西北约3962米"}],"warning":"对于自动采集者, 想要日弄你还是很简单的, 小心你的数据报废","latitude":"63.5816583324","longitude":"175.8781693333","match":"1"}
 */
	while(1)
	{
		if(getGpsSpg(460, 0, 34860, 62041, getDataStr, sizeof(getDataStr)) == 0)
		{
			fprintf(stderr, "%s\n", getDataStr);
		}
		else
		{
			fprintf(stderr, "Error Occur\n");
		}
		sleep(2);
		if(getGpsSpg(460, 1, 0x2531, 0x6a88202, getDataStr, sizeof(getDataStr)) == 0)
		{
			fprintf(stderr, "%s\n", getDataStr);
		}
		else
		{
			fprintf(stderr, "Error Occur\n");
		}
		sleep(2);
	}
	return 0;
}
/*
 * return: 0 success
 * 	   1 fail
 */
int getGpsSpg(int mcc,  /*Country, china 460*/
		int mnc, /*Mobile telecom carrier: 00 China Mobile 01 China Unicom 02 China Telecom*/
		int lac_tac,  /*LAC/TAC 1~65535*/
		int ci,    /*CI 2G(1~65535), 3G/4G(1~268435455)*/
		char *getDataStr,
		int getDataStrSize)
{
	int curTimeSecondsByUTC = 0;
	int nonce = 0; 
	char queryCmdStr[1024] = "";
	FILE *fp = NULL;
	char line[2048] = "";
	char *jsonBegin = NULL, *jsonEnd = NULL;
	char gpsspg_com_return_200_OK[] = "{\"status\":200,";
#define STORE_GPS_SPG_DATA "./.store_gps_spg_data"

	if(((time_t) -1) == (curTimeSecondsByUTC = time(NULL)))
	{
		fprintf(stderr, "%s %d, time(NULL) error: %s\n", strerror(errno));
		goto ERR;
	}
	nonce = curTimeSecondsByUTC % 1000;
	snprintf(queryCmdStr, sizeof(queryCmdStr), "wget --referer=\"http://www.gpsspg.com/bs.htm\"  --user-agent=\"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:52.0) Gecko/20100101 Firefox/52.0\" -O %s \"http://api.gpsspg.com/bss/?oid=159&bs=%d,%02d,%x,%x&hex=16&type=&to=1&output=jsonp&callback=jQuery110207972865504789974_%d%d&_=%d%d\" >/dev/null 2>&1", STORE_GPS_SPG_DATA, mcc, mnc, lac_tac, ci, curTimeSecondsByUTC, nonce, curTimeSecondsByUTC, (nonce+1) % 1000);
	system(queryCmdStr);
	if(0 != access(STORE_GPS_SPG_DATA, F_OK) ||
		NULL == (fp = fopen(STORE_GPS_SPG_DATA, "r")))
	{
		fprintf(stderr, "%s %d, file %s don't exist\n", STORE_GPS_SPG_DATA);
		goto ERR;
	}

	if(NULL == fgets(line, sizeof(line), fp))
	{
		goto ERR;
	}
	if(NULL == (jsonBegin = strchr(line, (int)'{')) ||
		NULL == (jsonEnd = strchr(line, (int)')')))
	{
		fprintf(stderr, "Data Format Error\n");
		goto ERR;
	}
	*jsonEnd = '\0';
	if(getDataStr != NULL && getDataStrSize > 1)
	{
		strncpy(getDataStr, jsonBegin, getDataStrSize);
	}
	if(0 != strncmp(getDataStr, gpsspg_com_return_200_OK, strlen(gpsspg_com_return_200_OK) - 1))
	{
		fprintf(stderr, "Return Error From Web, %s\n", getDataStr);
		exit(1);
		goto ERR;
	}
	if(fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
	return 0;
ERR:
	if(fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
	return -1;
}


