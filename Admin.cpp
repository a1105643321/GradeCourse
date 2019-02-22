#include "stdafx.h"
#include "Admin.h"
Admin::Admin()
{
}
Admin::~Admin()
{
}
void Admin::stuAllocate()
{
	TxtAnalysis tex;
	File  file;
	list<string> lstString;
	file.readStuFile("namelist.csv", lstString);
	tex.stuInfoAnalysis(lstString);
	file.writeHead(tex.getRevList());
	file.writeCode(tex.getRevList());
	tex.allocateStu();
}
void Admin::getRevRst()
{
	TxtAnalysis tex;
	File  file;
	list<string> lstString;
	file.readAllRst("acmilanzhu", lstString, "seed.bin");
}
void Admin::createSeed()
{


}