#include "Offer.h"
#include<string.h>
#include<iostream>
using namespace std;

//parameterized constructor
Offer::Offer(string role, string location, float pack, float bo, Date deadline, const Eligibility& eObj, vector<College> cvObj) :
	jobRole(role), jobLocation(location), package(pack), bond(bo), applicationDeadline(deadline), eligibilityCriteria(eObj) {
	collgeList = cvObj;
}

//Copy constructor
Offer::Offer(const Offer& of) {
	jobRole = of.jobRole;
	jobLocation = of.jobLocation;
	package = of.package;
	bond = of.bond;;
	applicationDeadline = of.applicationDeadline;
	eligibilityCriteria = of.eligibilityCriteria;
	collgeList = of.collgeList;
}

void Offer::operator=(const Offer& of) {
	jobRole = of.jobRole;
	jobLocation = of.jobLocation;
	package = of.package;
	bond = of.bond;;
	applicationDeadline = of.applicationDeadline;
	eligibilityCriteria = of.eligibilityCriteria;
	collgeList = of.collgeList;
}

void Offer::addCollege(College collgeObj) {
	collgeList.push_back(collgeObj);

	/* Insert in college table */
}

//setter methods
void Offer::setJobRole(string role)
{
	jobRole = role;
}

void Offer::setJobLocation(string location)
{
	jobLocation = location;
}

void Offer::setPackage(float pack)
{
	package = pack;
}

void Offer::setBond(float bond)
{
	bond = bond;
}

void Offer::setDeadline(Date deadline)
{
	applicationDeadline.setDay(deadline.getDay());
	applicationDeadline.setMonth(deadline.getMonth());
	applicationDeadline.setYear(deadline.getYear());
}

void Offer::setEligibility(Eligibility criteria)
{
	eligibilityCriteria = criteria;
}


//getter methods

vector<College>& Offer::getCollege() {
	return collgeList;
}

string Offer::getJobRole() const
{
	return jobRole;
}

string Offer::getJobLocation() const
{
	return jobLocation;
}

float Offer::getPackage() const
{
	return package;
}

float Offer::getBond() const
{
	return bond;
}

Date Offer::getDeadline() const
{
	return applicationDeadline;
}

Eligibility Offer::getEligibility() const
{
	return eligibilityCriteria;
}

void Offer::display() {
	cout << "Offer Details are as follows " << endl;
	cout << "Job Role :" << getJobRole() << endl;
	cout << "Job Location:" << getJobLocation() << endl;
	cout << "Package :" << getPackage() << endl;
    cout << "Bond:" << getBond() << endl;
	cout << "Application deadline : ";
	getDeadline().display();
    getDeadline().display();
	cout << endl;

	getEligibility().display();
    getEligibility().display();
}
