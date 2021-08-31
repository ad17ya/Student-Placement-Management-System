#pragma once

#include<iostream>
#include"Offer.h"
#include<vector>
#include<set>
using namespace std;

class Company
{
private:
	int companyID;
	string companyName;
	string companyEmail;
	string phoneNumber;
	vector<Offer> offers;
public:
	Company() = default;									//Default constructor
	Company(string, string, string, vector<Offer>);		//Parameterized constructor
	Company(const Company& c);							//Copy constructor
	void operator=(const Company&);

	void setName(string);
	void setEmail(string);
	void setPhoneNumber(string);
	void setOffer(Offer);

	string getName() const;
	string getEmail() const;
	string getPhoneNumber() const;
	int getComapanyID() const;

	vector<Offer> getOffers();

	void setPlacedStudents(set<int>, int);
	void showAppliedStudents(int);

	void display();

	~Company() = default;									//Destructor
};
