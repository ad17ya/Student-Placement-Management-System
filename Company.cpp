#include<iostream>
#include<string.h>
#include"Company.h"
#include<vector>
using namespace std;

void Company::setName(string n)
{
	name = n;
}

void Company::setEmail(string e)
{
	email = e;
}

void Company::setPhoneNumber(string pn)
{
	phoneNumber = pn;
}

void Company::setOffer(Offer of)
{
	offers.push_back(of);
}

string Company::getName()
{
	return name;
}

string Company::getEmail()
{
	return email;
}

string Company::getPhoneNumber()
{
	return phoneNumber;
}

vector<Offer> Company::getOffers()
{
	return offers;
}
