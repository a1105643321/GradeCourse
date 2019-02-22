// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TxtAnalysis.h"
#include "File.h"
#include "Admin.h"
#include "Reviewer.h"
void adminFunc()
{
	Admin admin;
	printf("1: Students File Allocate\n");
	printf("2: Students Score File Get\n");
	printf("3: Students Score Computing\n");
	printf("4: Creating Reviewer Code\n ");
	int operId = 0;
	cin >> operId;
	if (operId==1)
	{
		admin.stuAllocate();
	}
	if (operId==2)
	{
		admin.getRevRst();
	}
}

void reviewerFunc(string code)
{
	Reviewer reviewer;
	printf("1: Get Students List\n");
	printf("2: Write Rst\n");
	int operId = 0;
	cin >> operId;
	if (operId == 1)
	{
		reviewer.readBinFile(code);
	}
	if (operId == 2)
	{
		reviewer.writeBinFile(code);
	}
}





int _tmain(int argc, _TCHAR* argv[])
{
	string adminName = "acmilanzhu";
	string code;
	cout << "Input your code" << endl;
	cin >>code;
	if (code == adminName)
	{
		adminFunc();
	}
	else
	{
		reviewerFunc(code);
	}
	return 0;
}

