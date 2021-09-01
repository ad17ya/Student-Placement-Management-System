#include "College.h"
#include<string>
using namespace std;

// Constructor definition
College::College(string mCollegeName, int mCollegeCode, string mCollegeEmail, string mPhoneNumber, vector<Student> mStudentList) : collegeName(mCollegeName), collegeCode(mCollegeCode), collegeEmail(mCollegeEmail), phoneNumber(mPhoneNumber), studentList(mStudentList) {}

College::College(int cId,string mCollegeName, int mCollegeCode, string mCollegeEmail, string mPhoneNumber, vector<Student> mStudentList) : collegeId(cId),collegeName(mCollegeName), collegeCode(mCollegeCode), collegeEmail(mCollegeEmail), phoneNumber(mPhoneNumber), studentList(mStudentList) {}


// Copy Constructor
// College(const College &collegeObject) : collegeName(collegeObject.collegeName), collegeCode(collegeObject.collegeCode), collegeEmail(collegeObject.collegeEmail), phoneNumber(collegeObject.phoneNumber) , studentList(collegeObject.studentList)  {}



void College::addStudent(const Student& s) {
	studentList.push_back(s);
}

void College::addStudent(const Student& s,int collegeId) {
	studentList.push_back(s);

	sqlite3* DB;
	int exit;
	exit = sqlite3_open("campusDatabase.db", &DB);
	char* messageError;

	try {
		if (exit)
			throw exit;

		string sql;

		sql = "INSERT INTO STUDENT (studentName,studentDOB,studentEmail,studentPhoneNumber,studentDepartment,studentVerificationStatus,collegeId) VALUES ('" +
			s.getName() + "','" + to_string(s.getDate().getDay() + '/' + s.getDate().getMonth() + ' / ' +
			s.getDate().getYear())  + "','" + s.getEmail() + "','" + s.getPhoneNumber()+"','"+s.getDepartment()
			+"',0,"+ to_string(collegeId) + ")";


		int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);

		if (rc != SQLITE_OK)
			throw (short)1;

		sql = "INSERT INTO ELIGIBILITY (eligibilityCGPA,eligibilityLiveBacklog,eligibilityDeadBacklog,eligibilityPassingYear,eligibilityYearGap) VALUES (" +
			to_string(s.getEligibility().getCGPA()) + "," + to_string(s.getEligibility().getLiveBackLog()) + "," +
			to_string(s.getEligibility().getDeadBackLog()) + "," + to_string(s.getEligibility().getPassingYear()) + ","
			+ to_string(s.getEligibility().getYearGap()) + ")";

		rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);

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

void College::setCollegeId(int cId)
{
	collegeId = cId;
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

int College::getCollegeId() const
{
	return collegeId;
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

static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

void College::verifyStudent()
{
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("campusDatabase.db", &DB);
	string data("");

	// Pass queries to sql throught
	string sql("update student set studentVerificationStatus=1 where studentId IN (select e.studentId from Eligibility e,college_student_AcadmicDetails cs where e.CGPA = cs.CGPA and e.liveBacklog = cs.liveBacklog and e.deadBacklog = cs.deadBacklog and e.passingYear = cs.passingYear and e.yearGap = cs.yearGap and e.studentId = cs.studentId)");

	try
	{
		if (exit)
			throw exit;

		int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);
		std::cout << std::endl;


		if (rc != SQLITE_OK)
		{
			throw (short)-1;
		}

	}

	catch (int exit) {
		std::cout << "Exception caught" << std::endl;
		std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
	}

	catch (short rc) {
		std::cout << "Exception caught" << endl;
		std::cerr << "Error getting count " << endl;
	}

	// Close sqlite
	sqlite3_close(DB);

}

void College::viewEnrolledStudents()
{

	// Open SQLite database
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("campusDatabase.db", &DB);
	string data("");

	// Pass queries to sql throught
	string sql("SELECT studentId, studentName FROM STUDENT");

	try
	{
		if (exit)
			throw exit;

		std::cout << "Opened database successfully" << std::endl;

		int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);
		std::cout << std::endl;


		if (rc != SQLITE_OK)
		{
			throw (short)-1;
		}

		cout << "Operation OK!" << endl;
	}

	catch (int exit) {
		std::cout << "Exception caught" << std::endl;
		std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
	}

	catch (short rc) {
		std::cout << "Exception caught" << endl;
		std::cerr << "Error getting count " << endl;
	}

	// Close sqlite
	sqlite3_close(DB);
}

void College::viewPlacedStudents() {
	// Open SQLite database
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("campusDatabase.db", &DB);
	string data("");

	// Pass queries to sql throught
	string sql("SELECT studentId,studentName FROM COLLEGE_INTERMEDIATESTUDENTSTATUS WHERE status=1");

	try
	{
		if (exit)
			throw exit;

		std::cout << "Opened database successfully" << std::endl;

		int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);
		std::cout << std::endl;


		if (rc != SQLITE_OK)
		{
			throw (short)-1;
		}

		cout << "Operation OK!" << endl;
	}

	catch (int exit) {
		std::cout << "Exception caught" << std::endl;
		std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
	}

	catch (short rc) {
		std::cout << "Exception caught" << endl;
		std::cerr << "Error getting count " << endl;
	}

	// Close sqlite
	sqlite3_close(DB);

}

void College::updateStudentPlacedStatus()
{
	// Open SQLite database
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("campusDatabase.db", &DB);
	string data("");

	// Update all records of the students placed from temporary table to the college database
	string sql("update student set studentVerificationStatus=1 where studentId IN (select e.studentId from Eligibility e,college_student_AcadmicDetails cs here e.eligibilityCGPA = cs.CGPA and e.eligibilityLiveBacklog = cs.liveBacklog and e.eligibilityDeadBacklog = cs.deadBacklog and e.eligibilityPassingYear = cs.passingYear and e.eligibilityYearGap =cs.yearGap and e.studentId = cs.studentId)");

	try
	{
		if (exit)
			throw exit;

		std::cout << "Opened database successfully" << std::endl;

		int rc = sqlite3_exec(DB, sql.c_str(), NULL, NULL, NULL);
		std::cout << std::endl;


		if (rc != SQLITE_OK)
		{
			throw (short)-1;
		}

		cout << "Operation OK!" << endl;
	}

	catch (int exit) {
		std::cout << "Exception caught" << std::endl;
		std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
	}

	catch (short rc) {
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

void updateCollegeDatabase(College* o) {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	string sql;
	try {
		rc = sqlite3_open("campusDatabase.db", &db);

		if (rc) {
			throw string("database not open");
		}



		sql = "update College set collegeName = '" + o->getName() + "', collegePhone = '" + o->getPhoneNumber() + "', collegeEmail = '" + o->getEmail() + "',collegeCode = " + to_string(o->getCollegeCode()) + " where collegeId = " + to_string(o->getCollegeId());
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


void College::updateCollege(string field) {
	if (field == string("collegeName")) {
		cout << "enter new college name : ";
		string newName;
		cin >> newName;
		collegeName = newName;
		updateCollegeDatabase(this);
	}
	else if (field == string("collegePhone")) {
		cout << "enter new college Phone: ";
		string newCollegePhone;
		cin >> newCollegePhone;
		phoneNumber = newCollegePhone;
		updateCollegeDatabase(this);
	}
	else if (field == string("collegeEmail")) {
		cout << "enter new college email : ";
		string newEmail;
		cin >> newEmail;
		collegeEmail = newEmail;
		updateCollegeDatabase(this);
	}
	else if (field == string("collegeCode")) {
		cout << "enter new college code : ";
		int newCode;
		cin >> newCode;
		collegeCode = newCode;
		updateCollegeDatabase(this);
	}

}
