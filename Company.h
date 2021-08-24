#pragma once

#include<iostream>
#include"Offer.h"
#include<vector>
using namespace std;
class Company
{
private:
	string companyName;
	string companyEmail;
	string phoneNumber;
	vector<Offer> offers;
public:
	void setName(string);
	void setEmail(string);
	void setPhoneNumber(string);
	void setOffer(Offer);
	string getName();
	string getEmail();
	string getPhoneNumber();
	vector<Offer> getOffers();
	void setPlacedStudents();
	void showAppliedStudents();
};
