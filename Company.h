#pragma once

#include<iostream>
#include"Offer.h"
#include<vector>
#include<set>
using namespace std;

class Company
{
private:
	int companyId;
	string companyName;
	string companyEmail;
	string companyPhoneNumber;
	vector<Offer> offers;
public:
	Company() = default;									//Default constructor
	Company(string, string, string, vector<Offer>);		//Parameterized constructor
	Company(const Company& c);							//Copy constructor
	void operator=(const Company&);

	void setCompanyId(int);
	void setName(string);
	void setEmail(string);
	void setPhoneNumber(string);
	void setOffer(Offer,string);
	void setOffer(Offer);

	int getCompanyId() const;
	int getCompanyId(string) const;
	string getName() const;
	string getEmail() const;
	string getPhoneNumber() const;

	vector<Offer>& getOffers();

	Offer callback3(void* data, int argc, char** argv, char** azColName);


	void setPlacedStudents(set<int>, int);
	void showAppliedStudents(int);

	void display();
	

	~Company() = default;									//Destructor
};
