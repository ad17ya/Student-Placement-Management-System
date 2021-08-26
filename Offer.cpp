#include "Offer.h"
using namespace std;


void Offer::setJobRole(string s)
{
	jobRole = s;
}

void Offer::setJobLocation(string jl)
{
	jobLocation = jl;
}

void Offer::setPackage(float pk)
{
	package = pk;
}

void Offer::setBond(float b)
{
	bond = b;
}

void Offer::setDeadline(Date d)
{
	applicationDeadline.setDay(d.getDay());
	applicationDeadline.setMonth(d.getMonth());
	applicationDeadline.setYear(d.getYear());
}

void Offer::setEligibility(Eligibility e)
{
	eligibilityCriteria = e;
}

string Offer::getJobRole()
{
	return jobRole;
}

string Offer::getJobLocation()
{
	return jobLocation;
}

float Offer::getPackage()
{
	return package;
}

float Offer::getBond()
{
	return bond;
}

Date Offer::getDeadline()
{
	return applicationDeadline;
}

Eligibility Offer::getEligibility()
{
	return eligibilityCriteria;
}
