#pragma once
#include<iostream>
#include<vector>
#include"Skill.h"
using namespace std;
//add comments
//add namespaces
//
class Eligibility {
private:
	//Percentage
	float CGPA;
	int liveBackLog;	//ATKT (not cleared not while application)
	int deadBackLog;	//ATKT	(already cleared )
	int passingYear;	//year of graduation(eg .2021)
	int yearGap;	// gap after 12th or 10th standard 
	vector<Skill> requiredSkills;	//skills of student( array of skills)
public:
	Eligibility(float, int, int, int, string);
	void setCGPA(float);
	float getCGPA();
	void setLiveBackLog(int);
	int getLiveBackLog();
	void setDeadBackLog(int);
	int getDeadBackLog();
	void addSkills(string);
	int getYearGap();
	void setYearGap(int);
};

