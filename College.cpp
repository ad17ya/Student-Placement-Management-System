#include "College.h"
using namespace std;

// Constructor definition
College::College(string mCollegeName, int mCollegeCode, string mCollegeEmail, string mPhoneNumber, vector<Student> mStudentList) : collegeName(mCollegeName), collegeCode(mCollegeCode), collegeEmail(mCollegeEmail), phoneNumber(mPhoneNumber), studentList(mStudentList) {}

// Copy Constructor
// College(const College &collegeObject) : collegeName(collegeObject.collegeName), collegeCode(collegeObject.collegeCode), collegeEmail(collegeObject.collegeEmail), phoneNumber(collegeObject.phoneNumber) , studentList(collegeObject.studentList)  {}

void College::addStudent(const Student &s) {
	studentList.push_back(s);
}

void College::setName(string s)
{
	collegeName = s;
}

void College::setCollegeCode(int code)
{
	collegeCode = code;
}

void College::setEmail(string e)
{
	collegeEmail = e;
}

void College::setPhoneNumber(string pn)
{
	phoneNumber = pn;
}


// Getters

vector<Student>& College::getStudent() {
	return studentList;
}

string College::getName() const
{
	return collegeName;
}

int College::getCollegeCode() const 
{
	return collegeCode;
}

string College::getEmail() const 
{
	return collegeEmail;
}

string College::getPhoneNumber() const 
{
	return phoneNumber;
}

static int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char *)data);

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

void College::viewEnrolledStudents()
{

	// Open SQLite database
	sqlite3 *DB;
	int exit = 0;
	exit = sqlite3_open("db.sqlite3", &DB);
	string data("");

	// Pass queries to sql throught
	string sql("SELECT S.studentId_id, A.first_name, A.last_name, S.department FROM STUDENT_student S, auth_user A where S.id=A.id");

	try
	{
		if (exit)
			throw exit;

		std::cout << "Opened database successfully" << std::endl;

		int rc = sqlite3_exec(DB, sql.c_str(), callback, (void *)data.c_str(), NULL);
		std::cout << std::endl;


		if (rc != SQLITE_OK)
		{
			throw (short) -1;
		}

		cout << "Operation OK!" << endl;
	}

	catch(int exit) {
			std::cout << "Exception caught" << std::endl;
			std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
	}

	catch(short rc) {
			std::cout << "Exception caught" << endl;
			std::cerr << "Error getting count " << endl;
	}

	// Close sqlite
	sqlite3_close(DB);
}

void College::updateStudentPlacedStatus()
{
	// Open SQLite database
	sqlite3 *DB;
	int exit = 0;
	exit = sqlite3_open("db.sqlite3", &DB);
	string data("");

	// Update all records of the students placed from temporary table to the college database
	string sql("UPDATE Student_student placedOffer_id = (SELECT offerId_id from College_intermediatestudentstatus WHERE status = 1 AND Student_student.studentId_id = College_intermediatestudentstatus.studentId_id)");

	try
	{
		if (exit)
			throw exit;

		std::cout << "Opened database successfully" << std::endl;

		int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, NULL);
		std::cout << std::endl;


		if (rc != SQLITE_OK)
		{
			throw (short) -1;
		}

		cout << "Operation OK!" << endl;
	}

	catch(int exit) {
			std::cout << "Exception caught" << std::endl;
			std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
	}

	catch(short rc) {
			std::cout << "Exception caught" << endl;
			std::cerr << "Error updating placed students " << endl;
	}

	// Close sqlite
	sqlite3_close(DB);
}


void College::display() {
	cout << "College Details are as follows " << endl;
	cout << "College Code : " << getCollegeCode() << endl;
	cout << "Name :" << getName() << endl;
	cout << "Email:" << getEmail() << endl;
	cout << "Phone Number :" << getPhoneNumber() << endl;
}