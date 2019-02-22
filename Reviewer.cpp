#include "stdafx.h"
#include "Reviewer.h"


Reviewer::Reviewer()
{
}


Reviewer::~Reviewer()
{
}
void Reviewer::readBinFile(string code)
{
	int a;
	File  file;
	list<string> lstString;
	file.readBinFile(code, lstString,"allocate.bin");
	lstString.empty() ? printf("File Lost Or Code Error\n") : file.wirteStuFile("rst.csv", lstString);
	printf("Get File Success!\n");
	printf("input any  digit  to end!");
	scanf_s("%d", &a);
}
void Reviewer::writeBinFile(string code)
{
	File  file;
	list<string> lstString;
	int a;
	file.readStuFile("rst.csv", lstString);
	file.writeBinRst(code, lstString, 2,"seed.bin");
	printf("input any  digit  to end!");
  scanf_s("%d", &a); 
}