#pragma once
#include<iostream>
#include<vector>
#include"College.h"
#include"Date.h"
#include"Eligibility.h"
using namespace std;
//add comments

class Offer {
private:
	string jobRole;
	string jobLocation;
	float package;
	float bond;
	Date applicationDeadline;
	Eligibility eligibilityCriteria;
	vector<College> collegeList;

public:
	void setJobRole(string);
	void setJobLocation(string);
	void setPackage(float);
	void setBond(float);
	void setDeadline(Date);
	void setEligibility(Eligibility);
	string getJobRole();
	string getJobLocation();
	float getPackage();
	float getBond();
	Date getDeadline();
	Eligibility getEligibility();
};