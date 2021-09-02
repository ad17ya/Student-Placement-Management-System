#include "Offer.h"
#include<string>
#include<iostream>
using namespace std;

//parameterized constructor
Offer::Offer(string role, string location, float pack, float bo, Date deadline, const Eligibility& eObj, vector<College> cvObj) :
	jobRole(role), jobLocation(location), package(pack), bond(bo), applicationDeadline(deadline), eligibilityCriteria(eObj) {
	collgeList = cvObj;
}

Offer::Offer(int id,string role, string location, float pack, float bo, Date deadline, const Eligibility& eObj, vector<College> cvObj) :
	offerId(id),jobRole(role), jobLocation(location), package(pack), bond(bo), applicationDeadline(deadline), eligibilityCriteria(eObj) {
	collgeList = cvObj;
}

//Copy constructor
Offer::Offer(const Offer& of) {
	offerId = of.offerId;
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

void Offer::addCollege(College collgeObj,int offerId) {
	collgeList.push_back(collgeObj);
	
	sqlite3* DB;
	int exit;
	exit = sqlite3_open("D:\\persistent\\project_123\\Student-Placement-Management-System\\database\\campusDatabase.db", &DB);
	char* messageError;

	try {
		if (exit)
			throw exit;

		string sql;

		sql = "INSERT INTO COLLEGE  (collegeName,collegePhone,collegeEmail,collegeCode,offerId) VALUES ('" +
			collgeObj.getName() + "','" + collgeObj.getPhoneNumber() + "','" + collgeObj.getEmail() + "'," + to_string(collgeObj.getCollegeCode()) + "," +
			to_string(offerId) + ")";


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

	sqlite3_close(DB);

}

void Offer::setOfferId(int oId)
{
	offerId = oId;
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

int Offer::getOfferId() const
{
	return offerId;
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
	cout << "Bond: " << getBond() << endl;
	cout << "Application deadline : ";
	getDeadline().display();
	cout << endl;

	getEligibility().display();
}

College& Offer::search(string cName)
{
	vector<College> ::iterator it;

	for ( it = collgeList.begin() ; it != collgeList.end() ; it++)
	{
		if (it->getName() == cName)
			return *it;
	}

	throw string("College not found");
}


void updateOfferDatabase(Offer* o) {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	string sql;
	try {
		rc = sqlite3_open("D:\\persistent\\project_123\\Student-Placement-Management-System\\database\\campusDatabase.db", &db);



		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			throw string("database not open");
		}


		sql = "update Offer set offerRole = '" + o->getJobRole() + "',offerLocation = '" + o->getJobLocation() + "', offerBond = " + to_string(o->getBond()) + ", offerPackage = " + to_string(o->getPackage()) + " where offerId = " + to_string(o->getOfferId());
		rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);


		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			throw string("update operation failed");
		}
		sqlite3_close(db);
	}
	catch (string error) {
		cerr << error;
	}
}



void Offer::updateOffer(string field) {
	if (field == string("jobRole")) {
		cout << "enter new job role : ";
		string newRole;
		cin >> newRole;
		setJobRole(newRole);
		updateOfferDatabase(this);
	}
	else if (field == string("jobLocation")) {
		cout << "enter new job location : ";
		string newLocation;
		cin >> newLocation;
		setJobLocation(newLocation);
		updateOfferDatabase(this);
	}
	else if (field == string("package")) {
		cout << "enter new job package : ";
		float newPackage;
		cin >> newPackage;
		setPackage(newPackage);
		updateOfferDatabase(this);
	}
	else if (field == "bond") {
		cout << "enter new job bond : ";
		float newBond;
		cin >> newBond;
		setBond(newBond);
		updateOfferDatabase(this);
	}
}