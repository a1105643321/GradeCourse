#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include<list>
#include "Tools.h"
#include <vector>
#include <math.h>
#include <set>
#include "Student.h"
#include "File.h"
using namespace std;
class TxtAnalysis
{
public:
	TxtAnalysis();
	~TxtAnalysis();
	int stuInfoAnalysis(list<string> &lstTxt);
	void allocateStu();
	void allocateUnit(int revId);
	void getStrInfo(vector<CStudent> &vecStu, list<string> &lstRst);
	void allocateStuId(set<int> &setStuId, int revId, int allCnt);
	void delFulStu();
	vector<CStudent> &getRevList();
private:
	vector<CStudent> vecStu;
	vector<CStudent> vecRev;
	vector<int>  vecRevCode;
	File   file;
	int  groupCnt;
};

