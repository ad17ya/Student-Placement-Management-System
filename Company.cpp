#include<iostream>
#include<string.h>
#include"Company.h"
#include<vector>
#include<set>
#include<sqlite3.h>
using namespace std;

//parameterized constructor
Company::Company(string name, string email, string pnumber, vector<Offer> of) : companyName(name), companyEmail(email), phoneNumber(pnumber) {
	offers = of;
}

//Copy constructor
Company::Company(const Company& c) {
	companyName = c.companyName;
	companyEmail = c.companyEmail;
	phoneNumber = c.phoneNumber;
	offers = c.offers;
}

void Company::operator=(const Company& c) {
	companyName = c.companyName;
	companyEmail = c.companyEmail;
	phoneNumber = c.phoneNumber;
	offers = c.offers;

}


//setter methods
void Company::setName(string name)
{
	companyName = name;
}

void Company::setEmail(string email)
{
	companyEmail = email;
}

void Company::setPhoneNumber(string pnumber)
{
	phoneNumber = pnumber;
}

void Company::setOffer(Offer of)
{
	offers.push_back(of);
	std::cout << "Offer Set" << std::endl;
}

//getter methods
string const Company::getName()
{
	return companyName;
}

string const Company::getEmail()
{
	return companyEmail;
}

string const Company::getPhoneNumber()
{
	return phoneNumber;
}

vector<Offer> const Company::getOffers()
{
	return offers;
}

void Company::setPlacedStudents(set<int> studentIdList, int offerId) {
	char* messageError;
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("example.db", &DB);

	
	set<int> ::iterator itr;
	string query;

	try {
		if (exit)
			throw exit;

		for (itr = studentIdList.begin(); itr != studentIdList.end(); itr++) {
			//temporary table
			query = "UPDATE COLLEGE_INTERMEDIATESTUDENTSTATUS SET STATUS = 1 WHERE OFFERID_ID='%d' and STUDENTID_ID='%d'", offerId, * itr;
			int rc = sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError);

			if (rc != SQLITE_OK)
				throw (short) 1;
		}
	}

	catch (int exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	}

	catch (short i) {
		cout << "Error in updation of placed student :" << messageError;
	}

	sqlite3_close(DB);
}

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

void Company::showAppliedStudents(int offerId) {
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("db.sqlite3" , &DB);
	string data("CALLBACK FUNCTION");


	char* messageError;
	string query;

	try {
		if (exit)
			throw exit;

		query = "SELECT CI.STUDENTID_ID,AU.FIRSTNAME,AU.LASTNAME FROM COLLEGE_INTERMEDIATESTUDENTSTATUS CI,AUTH_USER AU WHERE CI.STUDENTID_ID=AU.STUDENTID_ID AND CI.OFFERID_ID = '%d'", offerId;
		int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, &messageError);
		if (rc != SQLITE_OK)
			throw (short)1;
	}

	catch (int exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	}

	catch (short i) {
		cout << "Error in showing applied student :" << messageError;
	}
	
	sqlite3_close(DB);
}