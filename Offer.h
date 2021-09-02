#pragma once
#include<iostream>
#include"Date.h"
#include"Eligibility.h"
#include"College.h"
#include<vector>
using namespace std;

class Offer {
private:
	int offerId;
	string jobRole;
	string jobLocation;
	float package;
	float bond;
	Date applicationDeadline;
	Eligibility eligibilityCriteria;
	vector<College> collgeList;

public:
	Offer() = default;														//Default constructor
	Offer(int,string, string, float, float, Date, const Eligibility&, vector<College>);		//Parameterized constructor
	Offer(string, string, float, float, Date, const Eligibility&, vector<College>);		//Parameterized constructor

	Offer(const Offer& of);												//Copy constructor
	void operator=(const Offer&);
	void addCollege(College);
	void addCollege(College,int);
	void setOfferId(int);
	void setJobRole(string);
	void setJobLocation(string);
	void setPackage(float);
	void setBond(float);
	void setDeadline(Date);
	void setEligibility(Eligibility);

	vector<College>& getCollege();
	string getJobRole() const;
	int getOfferId() const;

	string getJobLocation() const;
	float getPackage() const;
	float getBond() const;
	Date getDeadline() const;

	Eligibility getEligibility() const;

	void display();
	College& search(string);

	void updateOffer(string);
	~Offer() = default;														//Destructor
};
