#pragma once
#include <iostream>

#include <map>
using namespace std;
//add comments
//add namespaces

class Eligibility
{
private:
	//Percentage
	double CGPA;
	int liveBackLog;					//ATKT (not cleared not while application)
	int deadBackLog;					//ATKT (already cleared )
	int passingYear;					//year of graduation(eg .2021)
	int yearGap;						// gap after 12th or 10th standard
	map<string, int> skillExpertiseMap; // mapping between skill(c++, java) and its respective level (in advanced, beginer)

public:
	
	// Constructors
	Eligibility(double, int, int, int, int, string);
	Eligibility();
	Eligibility(const Eligibility&);

	// Operator overloads
	void operator=(const Eligibility&);
	bool operator==(const Eligibility& e) const;

	// Getters
	double getCGPA() const;
	int getLiveBackLog() const;
	int getDeadBackLog() const;
	int getYearGap() const;
	int getPassingYear() const;

	// Setters
	void setCGPA(double);
	void setLiveBackLog(int);
	void setDeadBackLog(int);
	void setYearGap(int);

	void addSkill(string, string);

	void display();
};
