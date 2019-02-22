#include "stdafx.h"
#include "File.h"
#include "Tools.h"

File::File()
{
}


File::~File()
{
}
void File::readStuFile(string strFileName, list<string> & lstStr)
{
	 ifstream inFile;
	inFile.open(strFileName.c_str());
	while (!inFile.eof())
	{
		string temp;
		getline(inFile, temp);
		temp.size()<5 ? temp="" : lstStr.push_back(temp);
	}
}
void File::wirteStuFile(string strFileName, list<string> & lstStr)
{
	ofstream outFile;
	outFile.open(strFileName);
	list<string>::iterator iter = lstStr.begin();
	while (iter != lstStr.end())
	{
		outFile << *iter << endl;
		iter++;
	}
	outFile.close();
}

void File::writeEvaRst(string strFileName, list<string> & lstStr)
{
	ofstream outFile;
	outFile.open(strFileName);
	srand((unsigned)time(NULL));
	list<string>::iterator iter = lstStr.begin();
	while (iter != lstStr.end())
	{
		outFile << *iter << endl;
	}
	outFile.close();
}
void File::wirteGroupRst(string revId, vector<CStudent> &vecRev)
{
	ofstream location_out;
	char ss[256] = {0};
	location_out.open(revId.c_str(), std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
	if (!location_out.is_open())
		return ;
	for (int i = 0; i < vecRev.size(); i++)
	{
		sprintf_s(ss, "%s,%s", vecRev[i].getLocId().c_str(), vecRev[i].getLink().c_str());
		location_out << ss << endl;
	}
	location_out.close();
}

void File::writeBinRst(string revId, list<string> &vecRev, int type, string filename)
{
	char buf[4096] = {0};
	char tBuf[4096] = { 0 };
	char* buffer=NULL;
	int filesize = 0;
	int rst = 0;
	string strRst="";
	loadBinFile(&buffer, &filesize, filename);
	list<string>::iterator iter = vecRev.begin();
	while (iter != vecRev.end())
	{
		strRst += (*iter + '\n');
		iter++;
	}
	memcpy(buf, strRst.c_str(), strRst.length());
	if (strRst[0] != 'A' && strRst[0] != 'B')
	{
		printf("File Error!\n");
		outBin.close();
		return;
	}
	encryptStr(buf, tBuf, 4096, ENCRYPT);
	memcpy(tBuf + 4000, revId.c_str(), revId.length());
	if (type == REVIEWER)
	{
		rst = checkMutiFile(buffer, tBuf, filesize);
		if (rst == MUTIL)
		{
			printf("Do not load your file Again!\n");
			return;
		}
	}
	if (rst == NONMUTIL || type == STUDENT)
	{
		outBin.write((char*)tBuf, 4096);
		printf("Success!\n");
	}
	outBin.close();

}
int File::loadBinFile(char** buf, int* len, string filename)
{
	outBin.open(filename, ios::in | ios::out | ios::binary | ios::app);
	filebuf *pbuf = outBin.rdbuf();
	*len = pbuf->pubseekoff(0, ios::end, ios::in);
	pbuf->pubseekpos(0, ios::in);
	char *   buffer = new  char[*len];
	pbuf->sgetn(buffer, *len);
	*buf = buffer;
	outBin.close();
	outBin.open(filename, ios::in | ios::out | ios::binary | ios::app);
	return *len;
}
int File::checkMutiFile(char *buf, char* tBuf, int size)
{
	int rst = -1;
	for (int i = 0; i < size&& (rst!=0);i+=4096)
	{
         rst=memcmp(buf + i, tBuf, 4096);
	}
	return rst == 0 ? MUTIL : NONMUTIL;
}


int File::readBinFile(string code, list<string> & lstStr,string filename)
{
	vector<string> vecRevId;
	char* buffer=NULL;
	int filesize = 0;
	int pos = 0;
	if (loadBinFile(&buffer, &filesize, filename) == 0)
	{
		cout << "File Lost Or  Code Error";
		return -1;
	}
	readHead(buffer, vecRevId);
	if (checkRevId(vecRevId, code,pos)!=-1)
	{
		readUnit(buffer, pos+1, lstStr);
	}
	wirteStuFile("rst.csv", lstStr);
	outBin.close();
	delete []buffer;
	return 0;
}
void File::readAllRst(string code, list<string> & lstStr, string filename)
{
	vector<string> vecRevId;
	char* buffer = NULL;
	int filesize = 0;
	int pos = 0;
	if (loadBinFile(&buffer, &filesize, filename) == 0)
	{
		cout << "File Lost Or  Code Error";
		return ;
	}
	for (int i = 1; i < filesize/4096;i++)
	{
		readUnit(buffer, i , lstStr);
	}
	wirteStuFile("total.csv", lstStr);
	outBin.close();
	delete[]buffer;
}


void File::writeCode(vector<CStudent> &vecRev)
{
	outBin.open("list.csv", ios::in | ios::out | ios::binary | ios::app);
	char enCode[64] = {0};
	char strCode[128] = { 0 };
	for (int i = 0; i < vecRev.size(); i++)
	{
		encryptRevId(vecRev[i].getLocId().c_str(), enCode, vecRev[i].getLocId().length(), ENCRYPT);
		sprintf_s(strCode, "%s,%s\n", vecRev[i].getLocId().c_str(), enCode);
		outBin.write((char*)strCode, strlen(strCode));
		memset(strCode, 0, 128);
	}
	outBin.close();
}
void File::writeHead(vector<CStudent> &vecRev)
{
	outBin.open("allocate.bin", ios::in | ios::out | ios::binary | ios::app);
	char buf[4096] = { 0 };
	char enbuf[4096] = { 0 };

	for (int i = 0; i < vecRev.size();i++)
	{
		strcat_s(buf, vecRev[i].getLocId().c_str());
		strcat_s(buf, ",");
	}
	buf[strlen(buf) - 1] = 0;
	//encryptRevId(buf, enbuf, 4096, ENCRYPT);
	encryptStr(buf, enbuf, 4096, ENCRYPT);
	outBin.write((char*)enbuf, 4096);
	outBin.close();

	outBin.open("seed.bin", ios::in | ios::out | ios::binary | ios::app);
	encryptStr(buf, enbuf, 4096, ENCRYPT);
	outBin.write((char*)enbuf, 4096);
	outBin.close();
}

void File::readHead(char* pBuf, vector<string> &vecCode)
{
	char sbuf[4096] = {0};
	char des[16] = {0};
	int pos = 0;
	int diff = 0;
	encryptStr(pBuf, sbuf, 4096, DECRYPT);
	while (getHeadStr(sbuf+pos, des, diff,','))
	{
		encryptRevId(des, des, strlen(des), ENCRYPT);
		vecCode.push_back(des);
		memset(des, 0, 16);
		pos += diff+1;
	}
}