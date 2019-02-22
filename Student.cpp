#include "stdafx.h"
#include "Student.h"


CStudent::CStudent()
{
}
CStudent::~CStudent()
{
}
void CStudent::setStuInfo(string &str, int type)
{
	char *src=new char[256];
	char *pdel = src;
	memset(src, 0, 256);
	char des[3][128] = { 0 };
	int i = 0;
	strcpy_s(src, strlen(str.c_str()) + 1, str.c_str());
	char *tmp = src;
	while (true)
	{
		tmp = strchr(src, ',');
		if (tmp!=NULL)
		{
			memcpy(des[i++], src, tmp - src);
			tmp++;  src = tmp;
		}
		else
		{
			memcpy(des[i++], src, strlen(src));
			break;
		}
	}
	m_locId = des[0];
	m_gId = des[1];
	m_stuLink = des[2];
	m_type = (m_locId[0] == 'A') ? 1 : 0;
	m_checkTime = 5;
	delete[]pdel;
}
int  CStudent::getType()
{
	return m_type;
}
int CStudent::getCheckTime()
{
	return m_checkTime;
}
void CStudent::setCheckTime(int m_checkTime)
{
	this->m_checkTime = m_checkTime;
}
string CStudent::getLocId()
{
	return m_locId;
}
string CStudent::getLink()
{
	return m_stuLink;
}
int CStudent::getGroupId()
{
	char p[3] = { 0 };
	p[0] = m_locId[2];
	p[1] = m_locId[3];
	return atoi(p);
}
int CStudent::getSocre()
{
	return m_score;
}