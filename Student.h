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

/*
Select type - User
1. company
2. college
3. student

Company
1. Insert
2. Modify
3. View company info
5. View enrolled students
4. Goto offers
5. Insert
6. Modify 
7. View all offers
8. Search for offer

College
1. Insert
2. Modify
3. Student Verification
4. Company Verification
5. View College info
6. Search Colleges
7. View Enrolled students
8. View placed students


Student
1. Insert
2. Modify
3. Send for verification
4. View eligible offers
5. Apply for offers