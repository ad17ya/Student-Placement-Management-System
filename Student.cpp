#include<iostream>
#include"Student.h"
#include<string.h>
#include<sqlite3.h>

using namespace std;

Student::Student() = default;

Student::Student(string studentName, int studentId, string studentEmail, string studentPhoneNumber, Date DOB, string stringDepartment, const Eligibility& studentAcademicDetails) : studentName(studentName), studentId(studentId), studentEmail(studentEmail), studentPhoneNumber(studentPhoneNumber), DOB(DOB), studentDepartment(studentDepartment), studentAcademicDetails(studentAcademicDetails)
{
}

void Student::setName(string s)
{
	studentName = s;
}

string Student::getName()
{
	return studentName;
}

void Student::setID(int i)
{
	studentId = i;
}

int Student::getID()
{
	return studentId;
}

void Student::setEmail(string e)
{
	studentEmail = e;
}

string Student::getEmail()
{
	return studentEmail;
}

void Student::setPhoneNumber(string ph)
{
	studentPhoneNumber = ph;
}

string Student::getPhoneNumber()
{
	return studentPhoneNumber;
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
	studentAcademicDetails.setCGPA(e.getCGPA());
	studentAcademicDetails.setDeadBackLog(e.getDeadBackLog());
	studentAcademicDetails.setLiveBackLog(e.getLiveBackLog());
	studentAcademicDetails.setYearGap(e.getYearGap());
}

Eligibility Student::getAcademicDetails()
{
	return studentAcademicDetails;
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


int* Student::getApplicableOffers()
{
	string sql("SELECT * from Company_offer INNER JOIN Company_criteria ON Company_offer.id = Company_criteria.offerId_id;");
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("campus.db", &DB);
	string data("CALLBACK FUNCTION");

	if (exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;

	int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);

	if (rc != SQLITE_OK)
		cerr << "Error SELECT" << endl;
	else {
		cout << "Operation OK!" << endl;
	}

	sqlite3_close(DB);
}
