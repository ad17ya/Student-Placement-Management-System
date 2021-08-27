#pragma once
#include<iostream>
#include"Date.h"
#include"Eligibility.h"
#include"College.h"
#include<vector>
using namespace std;

class Offer {
private:
	string jobRole;
	string jobLocation;
	float package;
	float bond;
	Date applicationDeadline;
	Eligibility eligibilityCriteria;
	vector<College> collgeList;

public:
	Offer() = default;														//Default constructor
	Offer(string, string, float, float, Date, const Eligibility&, vector<College>);		//Parameterized constructor
	Offer(const Offer& of);												//Copy constructor
	void operator=(const Offer&);

	void addCollege(College);
	void setJobRole(string);
	void setJobLocation(string);
	void setPackage(float);
	void setBond(float);
	void setDeadline(Date);
	void setEligibility(Eligibility);

	string const getJobRole();
	string const getJobLocation();
	float const getPackage();
	float const getBond();
	Date const getDeadline();
	Eligibility const getEligibility();

	~Offer() = default;														//Destructor
};
