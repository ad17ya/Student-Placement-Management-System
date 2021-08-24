#pragma once
#include<iostream>
#include<vector>
#include"Date.h"
#include"Skill.h"
#include"Eligibility.h"


using namespace std;

class Student {
private:
	string Name;
	int id;
	string studentEmail;
	string phoneNumber;
	Date DOB;
	string department;
	Eligibility academicDetails;

public:
	void setName(string);
	string getName();
	void setID(int);
	int getID();
	void setEmail(string);
	string getEmail();
	void setPhoneNumber(string);
	string getPhoneNumber();
	void setDOB(Date);
	Date getDate();
	void setAcademicDetails(Eligibility);
	Eligibility getAcademicDetails();
	void apply(int);
};