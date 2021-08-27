#include <iostream>
#include "Student.h"
#include <string>
#include <sqlite3.h>

using namespace std;

Student::Student() = default;

Student::Student(string studentName, int studentId, string studentEmail, string studentPhoneNumber, Date DOB, string studentDepartment, const Eligibility &studentAcademicDetails) : studentName(studentName), studentId(studentId), studentEmail(studentEmail), studentPhoneNumber(studentPhoneNumber), DOB(DOB), studentDepartment(studentDepartment), studentAcademicDetails(studentAcademicDetails)
{
}

void Student::setName(string s)
{
    studentName = s;
}

string const Student::getName()
{
    return studentName;
}

void Student::setID(int i)
{
    studentId = i;
}

int const Student::getID()
{
    return studentId;
}

void Student::setEmail(string e)
{
    studentEmail = e;
}

string const Student::getEmail()
{
    return studentEmail;
}

void Student::setPhoneNumber(string ph)
{
    studentPhoneNumber = ph;
}

string const Student::getPhoneNumber()
{
    return studentPhoneNumber;
}

void Student::setDOB(Date d)
{
    DOB.setDay(d.getDay());
    DOB.setMonth(d.getMonth());
    DOB.setYear(d.getYear());
}

Date const Student::getDate()
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

int Student ::callback(void *objPtr, int argc, char **argv, char **azColName)
{
    return ((Student *)objPtr)->callbackHelper(argv);
}

int Student::callbackHelper(char **argv)
{
    //fprintf(stderr, "%s: ", (const char*)data);
    //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    Eligibility *tempCriteria = new Eligibility(atof(argv[1]), atoi(argv[2]), atoi(argv[3]), 2021, atoi(argv[4]), string("cpp:1,java:2"));
    //Eligibility* studentAcademicDetails = new Eligibility(8.5, 0, 0, 2021, 0, string("cpp:1,java:2"));
    cout << tempCriteria->getLiveBackLog() << "\n";
    if ((studentAcademicDetails) == *(tempCriteria))
    {
        potentialOfferId.push_back(atoi(argv[0]));
        cout << "inside if\n";
    }
    delete tempCriteria;
    return 0;
}

vector<int> Student::getApplicableOffers()
{
    string sql("SELECT * from Company_offer INNER JOIN Company_criteria ON Company_offer.id = Company_criteria.offerId_id;");
    sqlite3 *DB;
    int exit = 0;
    exit = sqlite3_open("db.sqlite3", &DB);
    string data("CALLBACK FUNCTION");

    if (exit)
    {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return potentialOfferId;
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;

    int rc = sqlite3_exec(DB, sql.c_str(), callback, (void *)this, NULL);

    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;
    else
    {
        cout << "Operation OK!" << endl;
    }
    for (auto it : potentialOfferId)
    {
        cout << it << "\n";
    }

    sqlite3_close(DB);
    return potentialOfferId;
}

static int insertCallback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void Student::applyForCompany(int offerId)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    string comma = ",";
    string sql(string("INSERT INTO College_intermediatestudentstatus (offerId_id, status, studentId_id) VALUES (") + to_string(offerId) + string(",0,") + to_string(studentId) + string(");"));

    /* Open database */
    rc = sqlite3_open("db.sqlite3", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }
    rc = sqlite3_exec(db, sql.c_str(), insertCallback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
}
