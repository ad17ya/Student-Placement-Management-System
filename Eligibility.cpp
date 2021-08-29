#include <iostream>
#include "Eligibility.h"
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

Eligibility::Eligibility(double cgpa, int lb, int db, int yP, int yG, string skillSet) : CGPA(cgpa), liveBackLog(lb), deadBackLog(db), yearGap(yG), passingYear(yP)
{
	//skill1:level1,skill2:level2...
	char *token;
	const char *delim = ",";
	char *next_token;
	token = strtok(const_cast<char *>(skillSet.c_str()), delim);
	while (token != NULL)
	{
		string s(token);
		size_t pos = s.find(":");
		skillExpertiseMap[s.substr(0, pos)] = stoi(s.substr(pos + 1, string::npos));
		token = strtok(NULL, delim);
	}
}

Eligibility::Eligibility() = default;

Eligibility::Eligibility(const Eligibility &e) : CGPA(e.CGPA), liveBackLog(e.liveBackLog), deadBackLog(e.deadBackLog), yearGap(e.yearGap), passingYear(e.passingYear)
{
	for (auto it : e.skillExpertiseMap)
	{
		skillExpertiseMap[it.first] = it.second;
	}
}

void Eligibility::operator=(const Eligibility &e)
{
	CGPA = e.CGPA;
	liveBackLog = e.liveBackLog;
	deadBackLog = e.deadBackLog;
	yearGap = e.yearGap;
	passingYear = e.passingYear;
	for (auto it : e.skillExpertiseMap)
	{
		skillExpertiseMap[it.first] = it.second;
	}
}

//student on lhs of == operator
/*
*/
bool Eligibility::operator==(const Eligibility &e) const
{
	cout << "in ==\n";
	if (CGPA >= e.CGPA && liveBackLog <= e.liveBackLog && deadBackLog <= e.deadBackLog && yearGap <= e.yearGap && passingYear == e.passingYear)
	{
		for (auto it : e.skillExpertiseMap)
		{
			auto findIterator = skillExpertiseMap.find(it.first);
			if (findIterator != skillExpertiseMap.end())
			{
				if (findIterator->second < it.second)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void Eligibility::setCGPA(double cgpa)
{
	CGPA = cgpa;
}

double Eligibility::getCGPA() const
{
	return CGPA;
}

void Eligibility::setLiveBackLog(int lb)
{
	liveBackLog = lb;
}

int Eligibility::getLiveBackLog() const
{
	return liveBackLog;
}

void Eligibility::setDeadBackLog(int db)
{
	deadBackLog = db;
}

int Eligibility::getDeadBackLog() const
{
	return deadBackLog;
}

int Eligibility::getYearGap() const
{
	return yearGap;
}

void Eligibility::setYearGap(int yg)
{
	yearGap = yg;
}

void Eligibility::addSkill(string skillName, string skillLevel)
{
	skillExpertiseMap[skillName] = stoi(skillLevel);
}

void Eligibility::display()
{
	cout << "Eligibility Criteria is " << endl;
	cout << "CGPA : " << getCGPA() << endl;
	cout << "Live Backlog : " << getLiveBackLog() << endl;
	cout << "Dead Backlog : " << getDeadBackLog() << endl;
	cout << "Passing year " << getYearGap() << endl;

	cout << "Skills\tExpertise Level " << endl;
	map<string, int>::iterator itr;

	for (itr = skillExpertiseMap.begin(); itr != skillExpertiseMap.end(); ++itr) {
		cout << itr->first << '\t' << itr->second << '\n';
	}
}