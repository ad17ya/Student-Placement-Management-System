#include<iostream>
#include"Eligibility.h"
#include<string.h>
#include<vector>
using namespace std;

Eligibility::Eligibility(float cgpa, int lb, int db, int gp, string skillSet): CGPA(cgpa), liveBackLog(lb), deadBackLog(db), yearGap(gp)
{
	//skill1:level1,skill2:level2...
	
}

void Eligibility::setCGPA(float cgpa)
{
	CGPA = cgpa;
}

float Eligibility::getCGPA()
{
	return CGPA;
}

void Eligibility::setLiveBackLog(int lb)
{
	liveBackLog = lb;
}

int Eligibility::getLiveBackLog()
{
	return liveBackLog;
}

void Eligibility::setDeadBackLog(int db)
{
	deadBackLog = db;
}

int Eligibility::getDeadBackLog()
{
	return deadBackLog;
}

/*void Eligibility::addSkill(Skill s)
{
	requiredSkills.push_back(s);
}*/



int Eligibility::getYearGap()
{
	return yearGap;
}

void Eligibility::setYearGap(int yg)
{
	yearGap = yg;
}
