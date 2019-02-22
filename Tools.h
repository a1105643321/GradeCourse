#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include<list>
#include <math.h>
#include<stdio.h>
#include <vector>
using namespace std;

#define   ENCRYPT 1
#define  DECRYPT   2

#define  STUDENT 1
#define  REVIEWER   2

#define  MUTIL    -1
#define  NONMUTIL 0
void  encryptStr(char* ebuf, char* tbuf, int len, int type);
int getHeadStr(char* src, char *des,int &len, char nos);
int checkRevId(vector<string> vecCode, string code, int &num);
void readUnit(char* buf, int pos, list<string> &lstStr);
void encryptRevId(const char* ebuf, char* tbuf, int len, int type);
void  encryptStr(char* ebuf, char* tbuf, int len, int type);