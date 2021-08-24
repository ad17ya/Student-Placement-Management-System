#include "Offer.h"
#include<string.h>
#include<iostream>
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
	deadline.setDay(d.getDay());
	deadline.setMonth(d.getMonth());
	deadline.setYear(d.getYear());
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
	return deadline;
}

Eligibility Offer::getEligibility()
{
	return eligibilityCriteria;
}
