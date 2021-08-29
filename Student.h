#pragma once
#include <iostream>
#include <vector>
#include "Date.h"
#include "Eligibility.h"
//#include"Offer.h"
#include <sqlite3.h>

using namespace std;

//Class describing student personal details and also academic details

class Student
{
private:
	string studentName;
	int studentId;
	string studentEmail;
	string studentPhoneNumber;
	Date DOB;
	string studentDepartment;

	Eligibility studentAcademicDetails; // data member describing student academic details
	vector<int> potentialOfferId;
	int callbackHelper(char **argv);

public:
	//make get method const
	Student();
	Student(string, int, string, string, Date, string, const Eligibility &);
	Student(const Student &) = default;


	//getters
	string getName() const;
	int getID() const;
	string getEmail() const;
	string getPhoneNumber() const;
	Date getDate() const;

	//methods
	void setName(string);
	void setID(int);
	void setEmail(string);
	void setPhoneNumber(string);
	void setDOB(Date);
	void setAcademicDetails(Eligibility);

	Eligibility getAcademicDetails();
	vector<int> getApplicableOffers();
	void applyForCompany(int); // int is offerid
	static int callback(void *, int, char **, char **);
	void display();
};