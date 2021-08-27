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
string const Offer::getJobRole()
{
	return jobRole;
}

string const Offer::getJobLocation()
{
	return jobLocation;
}

float const Offer::getPackage()
{
	return package;
}

float const Offer::getBond()
{
	return bond;
}

Date const Offer::getDeadline()
{
	return applicationDeadline;
}

Eligibility const Offer::getEligibility()
{
	return eligibilityCriteria;
}
