#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include<list>
#include <vector>
#include <time.h>
#include<stdio.h>
#include "Student.h"
using namespace std;
class File
{
public:
	File();
	~File();
	void readStuFile(string strFileName, list<string> & lstStr);
	void wirteStuFile(string strFileName, list<string> & lstStr);
	int readBinFile(string code, list<string> & lstStr, string filename);
	int checkMutiFile(char *buf, char* tBuf, int size);
	int loadBinFile(char** buf, int* len, string fileName);
	void wirteGroupRst(string  revId, vector<CStudent> &vecRev);
	void writeBinRst(string  revId, list<string> &lstRst,int type, string filename);
	void writeEvaRst(string strFileName, list<string> & lstStr);
	void writeHead(vector<CStudent> &vecRev);
	void writeCode(vector<CStudent> &vecRev);
	void readHead(char* pBuf, vector<string>& vecCode);
	void readAllRst(string code, list<string> & lstStr, string filename);
private:
	ofstream inBin;
	fstream  outBin;
};

