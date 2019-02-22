#include "stdafx.h"
#include "TxtAnalysis.h"


TxtAnalysis::TxtAnalysis()
{

}


TxtAnalysis::~TxtAnalysis()
{
}
int TxtAnalysis::stuInfoAnalysis(list<string> &lstTxt)
{
	list<string>::iterator iter = lstTxt.begin();
	string strTmp[3];
	CStudent tmpStu;
	while (iter != lstTxt.end())
	{
		tmpStu.setStuInfo(*iter++, 1);
		vecStu.push_back(tmpStu);
		if (tmpStu.getType()==1)
		{
			vecRev.push_back(tmpStu);
		}
	}
	vecStu.push_back(tmpStu);
	return 0;
}
void TxtAnalysis::allocateStu()
{
	groupCnt = vecStu.size() * 5 / vecRev.size() + 1;
	for (int i = 0; i < vecRev.size();i++)
	{
		allocateUnit(i);
		cout << "FileId="<<i<<vecRev[i].getLocId() << endl;
	}
}
vector<CStudent>& TxtAnalysis::getRevList()
{
	return vecRev;
}
void TxtAnalysis::getStrInfo(vector<CStudent> &vecStu, list<string> &lstRst)
{  
	string str;
	for (int i = 0; i < vecStu.size();i++)
	{
		str += vecStu[i].getLocId() + "," + vecStu[i].getLink();
		lstRst.push_back(str);
		str = "";
	}
}


void TxtAnalysis::allocateUnit( int revId)
{
	set<int> setNum;
	list<string> lstRst;
	allocateStuId(setNum, vecRev[revId].getGroupId(), groupCnt);
	vector<CStudent> vTmpStu;
	set<int>::iterator iter = setNum.begin();
	for (int i = 0; i < setNum.size();i++)
	{
		vTmpStu.push_back(vecStu[*iter]);
		int time = vecStu[*iter].getCheckTime() - 1;
		vecStu[*iter++].setCheckTime(time);
	}
	delFulStu();
	getStrInfo(vTmpStu, lstRst);
	file.writeBinRst("allocate.bin", lstRst, STUDENT,"allocate.bin");
}
void TxtAnalysis::allocateStuId(set<int> &setNum, int groupId,int allCnt)
{
	if (vecStu.size() <=allCnt)
	{
		for (int i = 0; i < vecStu.size() - 1;i++)
		{
			setNum.insert(i);
		}
		return;
	}
	int selectTime = 0;
	srand((unsigned)time(NULL));
	while (setNum.size() != allCnt)
	{
		int num = rand() % vecStu.size();
		if (groupId != vecStu[num].getGroupId())
		{
			setNum.insert(num);
		}
		if (selectTime++>10000)
		{
			break;
		}
	}
}
void TxtAnalysis::delFulStu()
{
	for (int i = 0; i < vecStu.size() || (vecStu.size() == 1);)
	{
		if (vecStu[i].getCheckTime() == 0)
		{
			vecStu.erase(vecStu.begin()+i);
			continue;
		}
		i++;
	}
}