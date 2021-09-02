#include<iostream>
#include<string>
#include"Company.h"
#include"Offer.h"
#include<vector>
#include<set>
#include<sqlite3.h>
using namespace std;

int result;

static int callback2(void* data, int argc, char** argv, char** azColName)
{

	result = argv[0] ? atoi(argv[0]) : -1;
	return result;

}

//parameterized constructor
Company::Company(string name, string email, string pnumber, vector<Offer> of) : companyName(name), companyEmail(email), companyPhoneNumber(pnumber) {
	offers = of;

	sqlite3* DB;
	int exit;
	exit = sqlite3_open("campusDatabase.db", &DB);
	char* messageError;

	try {
		if (exit)
			throw exit;

		string sql;
		sql = "SELECT companyid FROM Company where companyName like '" + name+"'";
		int companyId = sqlite3_exec(DB, sql.c_str(), callback2, NULL, &messageError);

		if (companyId != 0)
			throw (char)1;

		sql = "INSERT INTO COMPANY(companyName,companyPhoneNumber,companyEmail) VALUES ('" +
			name + "','" + pnumber + "','" + email  + "')";


		int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);

		if (rc != SQLITE_OK)
			throw (short)1;

	}

	catch (int exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	}

	catch (short i) {
		cout << "Error in Insert Data :";
	}

	catch (char str) {
	}

	sqlite3_close(DB);

}

//Copy constructor
Company::Company(const Company& c) {
	companyName = c.companyName;
	companyEmail = c.companyEmail;
	companyPhoneNumber = c.companyPhoneNumber;
	offers = c.offers;
}

void Company::operator=(const Company& c) {
	companyName = c.companyName;
	companyEmail = c.companyEmail;
	companyPhoneNumber = c.companyPhoneNumber;
	offers = c.offers;

}


void Company::setCompanyId(int cId)
{
	companyId = cId;
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
	companyPhoneNumber = pnumber;
}



void Company::setOffer(Offer of,string cName)
{
	offers.push_back(of);
//	std::cout << "Offer Set" << std::endl;

	sqlite3* DB;
	int exit ;
	exit = sqlite3_open("campusDatabase.db", &DB);
	char* messageError;

	try {
		if (exit)
			throw exit;

		string sql;

		sql = "INSERT INTO OFFER  (offerPackage,offerLocation,offerRole,offerDeadline,offerBond,CompanyId) VALUES (" +
			to_string(of.getPackage()) + ",'" + of.getJobLocation() + "','" + of.getJobRole() + "','"+
			to_string(of.getDeadline().getDay() + '/' + of.getDeadline().getMonth() + ' / ' +
			of.getDeadline().getYear())+"'," +to_string(of.getBond()) + ", " +to_string(getCompanyId(cName)) + ")";

		int rc= sqlite3_exec(DB, sql.c_str(),NULL, NULL, &messageError);

		if (rc != SQLITE_OK)
			throw (short)1;

		sql = "SELECT max(offerId) from Offer";

		int offerId = sqlite3_exec(DB, sql.c_str(), callback2, (void*)&result, &messageError);
		cout << result;


		sql = "INSERT INTO OfferEligibility(eligibilityCGPA,eligibilityLiveBacklog,eligibilityDeadBacklog, eligibilityPassingYear, eligibilityYearGap, offerId) VALUES ("
			+ to_string(of.getEligibility().getCGPA()) + "," + to_string(of.getEligibility().getLiveBackLog()) + "," + to_string(of.getEligibility().getDeadBackLog()) +
			"," + to_string(of.getEligibility().getPassingYear()) + "," + to_string(of.getEligibility().getYearGap()) + ","
			+ to_string(result) + ")";


		rc=sqlite3_exec(DB, sql.c_str() ,NULL , NULL, &messageError);

	}

	catch (int exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	}

	catch (short i) {
		cout << "Error in Insert Data :" ;
	}

	sqlite3_close(DB);

}

void Company::setOffer(Offer of) {
	offers.push_back(of);
}

//getter methods
string Company::getName() const
{
	return companyName;
}

string Company::getEmail() const
{
	return companyEmail;
}

string Company::getPhoneNumber() const
{
	return companyPhoneNumber;
}


vector<Offer>& Company::getOffers()
{
	return offers;
}


void Company::setPlacedStudents(set<int> studentIdList, int offerId) {
	char* messageError;
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("campusDatabase.db", &DB);


	set<int> ::iterator itr;
	string query;

	try {
		if (exit)
			throw exit;

		for (itr = studentIdList.begin(); itr != studentIdList.end(); itr++) {

			query = "UPDATE COLLEGE_INTERMEDIATESTUDENTSTATUS SET STATUS = 1 WHERE OFFERID=" +
				to_string(offerId) + " and STUDENTID=" + to_string(*itr);
			int rc = sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError);

			if (rc != SQLITE_OK)
				throw (short)1;
		}
	}

	catch (int exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	}

	catch (short i) {
		cout << "Error in updation of placed student :";
	}

	sqlite3_close(DB);
}

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

void Company::showAppliedStudents(int offerId) {
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("campusDatabase.db", &DB);


	char* messageError;
	string query;

	try {
		if (exit)
			throw exit;

		query = "SELECT CI.STUDENTID,S.STUDENTNAME FROM COLLEGE_INTERMEDIATESTUDENTSTATUS CI,STUDENT S WHERE CI.STUDENTID=S.STUDENTID AND CI.OFFERID =" + to_string(offerId);
		int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, &messageError);

		if (rc != SQLITE_OK)
			throw (short)1;
	}

	catch (int exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	}

	catch (short i) {
		cout << "Error in showing applied student :";
	}

	sqlite3_close(DB);
}

void Company::display() {
	cout << "Company Details are as follows " << endl;

	cout << "Name :" << getName() << endl;
	cout << "Email:" << getEmail() << endl;
	cout << "Phone Number :" << getPhoneNumber() << endl;
}

Offer& Company::search(string oName)
{
	vector<Offer> ::iterator it;

	for (it = offers.begin(); it != offers.end(); it++) {
		if (it->getJobRole() == oName) {
			return *it;
		}
	}

	throw string("not found");
}

void Company::sort()
{
	sqlite3* DB;
	int exit;
	exit = sqlite3_open("campusDatabase.db", &DB);
	char* messageError;

	try {
		if (exit)
			throw exit;

		string sql;
		sql = "SELECT offerRole,offerLocation,offerPackage FROM Offer ORDER BY offerPackage DESC" ;
		int rc = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);


		if (rc != SQLITE_OK)
			throw (short)1;

	}

	catch (int exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	}

	catch (short i) {
		cout << "Error in Insert Data :";
	}


	sqlite3_close(DB);


}

int Company::getCompanyId() const
{
	return companyId;
}

int Company::getCompanyId(string cname) const
{
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("campusDatabase.db", &DB);
	char* messageError;

	try {
		if (exit)
			throw exit;

		string sql;
		sql = "SELECT companyid FROM Company where companyName=" + cname;
		int companyId = sqlite3_exec(DB, sql.c_str(), callback2, NULL, &messageError);

		if (companyId == 0)
			throw (short)1;
		return companyId;
	}

	catch (int exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
	}

	catch (short i) {
		cout << "Company not fonund :" ;
	}

	return 0;
}
