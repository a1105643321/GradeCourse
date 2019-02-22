#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include<list>
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include<list>
#include <time.h>
#include <math.h>
#include<stdio.h>
#include "File.h"
using namespace std;
class Reviewer
{
public:
	Reviewer();
	~Reviewer();
	void readBinFile(string code);
	void writeBinFile(string code);
private: 
	string revLocId;
	string code;
};

