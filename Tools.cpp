#include "stdafx.h"
#include "Tools.h"

int checkRevId(vector<string> vecCode, string code, int &num)
{
	for (int i = 0; i < vecCode.size(); i++)
	{
		if (vecCode[i] == code)
		{
			num = i;
			return i;
		}
	}
	return -1;
}
void readUnit(char* buf, int pos, list<string> &lstStr)
{
	char tmpBuf[4096] = { 0 };
	encryptStr(buf + pos * 4096, tmpBuf, 4096, DECRYPT);
	char tmp[128] = { 0 };
	int rst = 1;
	int locPos = 0;
	while (rst >0)
	{
		rst = getHeadStr(tmpBuf + locPos, tmp, rst, '\n');
		if (rst >0)
		{
			lstStr.push_back(tmp);
			memset(tmp, 0, 128);
			locPos += rst+1;
		}
	}
}
int getHeadStr(char* src, char *des, int &len,char nos)
{
	char *tmp = src;
	if (src == NULL || strlen(src) < 2)
	{
		return 0;
	}
	if (strlen(src) > 2)
	{
		tmp = strchr(src, nos);
		if (tmp==NULL)
		{
			memcpy(des, src, strlen(src));
			return strlen(src);
		}
		memcpy(des, src, tmp - src);
	}
	len = tmp - src;
	return (tmp - src > 0) ? tmp - src : 0;
}
void encryptRevId(const char* ebuf, char* tbuf, int len, int type)
{
	int code[16] = {3, 4, 10, 8, 3, 9, 4, 9, 8,6,12,14,15,10 ,13,3};
	static int pos = 0;
	len = strlen(ebuf);
	if (type == ENCRYPT)
	{
		for (int i = 0; i < len; i++)
		{
			tbuf[i] = (ebuf[i] == 'A') ? (ebuf[i] + code[pos++ % 16]) : ebuf[i] + 16 + code[pos++ % 16];
		}
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			tbuf[i] = (ebuf[i] - code[pos++ % 16] == 'A') ? (ebuf[i] - code[pos++ % 16]) : ebuf[i] - 16 - code[pos++ % 16];
		}
	}
}




void  encryptStr(char* ebuf, char* tbuf, int len, int type)
{
	int code[16] = {3, 4, 6, 8, 9, 22, 19, 27, 24, 7, 19, 11, 15, 19, 18, 13 };
	if (type == ENCRYPT)
	{
		for (int i = 0; i < len-100; i++)
		{
			tbuf[i] = ebuf[i] + code[i % 16];
		}
	}
	else
	{
		for (int i = 0; i < len - 100; i++)
		{
			tbuf[i] = ebuf[i] - code[i % 16];
		}
	}
}
