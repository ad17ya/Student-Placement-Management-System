#include<iostream>
#include"Student.h"
#include<string.h>
using namespace std;

void Student::setName(string s)
{
	name = s;
}

string Student::getName()
{
	return name;
}

void Student::setID(int i)
{
	id = i;
}

int Student::getID()
{
	return id;
}

void Student::setEmail(string e)
{
	email = e;
}

string Student::getEmail()
{
	return email;
}

void Student::setPhoneNumber(string ph)
{
	phoneNumber = ph;
}

string Student::getPhoneNumber()
{
	return phoneNumber;
}

void Student::setDOB(Date d)
{
	DOB.setDay(d.getDay());
	DOB.setMonth(d.getMonth());
	DOB.setYear(d.getYear());
}

Date Student::getDate()
{
	return DOB;
}

void Student::setAcademicDetails(Eligibility e)
{
	academicDetails.setCGPA(e.getCGPA());
	academicDetails.setDeadBackLog(e.getDeadBackLog());
	academicDetails.setLiveBackLog(e.getLiveBackLog());
	academicDetails.setYearGap(e.getYearGap());
}

Eligibility Student::getAcademicDetails()
{
	return academicDetails;
}
