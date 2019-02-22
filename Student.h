#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include<list>
#include <time.h>
#include <math.h>
#include<stdio.h>
using namespace std;
class CStudent
{
public:
	CStudent();
	~CStudent();
	//CStudent& operator=(const CStudent& stu);
	void setStuInfo(string &str, int type);
	int    getType();
	string getLocId();
	string  getLink();
	int    getCheckTime();
	void setCheckTime(int m_checkTime);
	int   getGroupId();
	int   getSocre();
private:
	string m_gId;
	string m_locId;
	string m_stuLink;
	int  m_score;
	int  m_type;
	int m_checkTime;
};

