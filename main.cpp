#include <iostream>
#include<string>
#include "Eligibility.h"
#include <sqlite3.h>
#include "Student.h"
#include <vector>
#include <string.h>
#include "College.h"
#include "Company.h"
#include "Date.h"
#include "Offer.h"
#include<map>
using namespace std;


// Returns offer index
int getIndexOffer(Company& c, int id) {
    for (int i = 0; i < c.getOffers().size(); i++) {
        if (c.getOffers()[i].getOfferId() == id) {
            return i;
        }
    }
    return -1;
}

int getIndexCollege(Company& c, int offerId, int collegeId) {
    for (int i = 0; i < c.getOffers().at(getIndexOffer(c, offerId)).getCollege().size(); i++) {
        if (c.getOffers().at(getIndexOffer(c, offerId)).getCollege()[i].getCollegeId() == collegeId) {
            return i;
        }
    }
    return -1;
}

int getIndexStudent(Company& c, int offerId, int collegeId, int studentId) {
    for (int i = 0; i < c.getOffers().at(getIndexOffer(c, offerId)).getCollege().at(getIndexCollege(c, offerId, collegeId)).getStudent().size(); i++) {
        if (c.getOffers().at(getIndexOffer(c, offerId)).getCollege().at(getIndexCollege(c, offerId, collegeId)).getStudent()[i].getID() == studentId)
            return i;
    }
    return -1;
}

static int callback(void* data, int argc, char** argv, char** azColName)
{
    //    cout << "in callback";
    int i;
    *(int*)data = atoi(argv[0]);
    return 0;
}

static int companyCallback(void* data, int argc, char** argv, char** azColName)
{
    (*(Company*)data).setCompanyId(atoi(argv[0]));
    (*(Company*)data).setName(argv[1]);
    (*(Company*)data).setPhoneNumber(argv[2]);
    (*(Company*)data).setEmail(argv[3]);
    return 0;
}

static int offerCallback(void* data, int argc, char** argv, char** azColName)
{
    (*(Company*)data).setOffer(Offer(atoi(argv[0]), argv[3], argv[2], atof(argv[1]), atof(argv[5]), Date(12,12,2021), Eligibility(), vector<College>()));
    return 0;
}

static int collegeCallback(void* data, int argc, char** argv, char** azColName)
{
    int offerIndex = getIndexOffer((*(Company*)data), atoi(argv[4]));
    (*(Company*)data).getOffers().at(offerIndex).addCollege(College(atoi(argv[0]), argv[1], atoi(argv[5]), argv[3], argv[2], vector<Student>()));
    return 0;
}

int offerId, collegeId;
static int studentCallback(void* data, int argc, char** argv, char** azColName)
{
    int offerIndex = getIndexOffer((*(Company*)data), offerId);
    int collegeIndex = getIndexCollege((*(Company*)data), offerId, atoi(argv[7]));
    if (collegeIndex != -1) {
        (*(Company*)data).getOffers().at(offerIndex).getCollege().at(collegeIndex).addStudent(Student(argv[1], atoi(argv[0]), argv[3], argv[4], Date(11,12,1999), argv[5], Eligibility()));
    }
    return 0;
}

static int studentEligibilityCallback(void* data, int argc, char** argv, char** azColName)
{
    int offerIndex = getIndexOffer((*(Company*)data), offerId);
    int collegeIndex = getIndexCollege((*(Company*)data), offerId, collegeId);
    int studentIndex = getIndexStudent((*(Company*)data), offerId, collegeId, atoi(argv[6]));
    if (studentIndex != -1) {
        (*(Company*)data).getOffers().at(offerIndex).getCollege().at(collegeIndex).getStudent().at(studentIndex).setAcademicDetails(Eligibility(atof(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), string("c++:1,java:2")));
    }
    return 0;
}

static int offerEligibilityCallback(void* data, int argc, char** argv, char** azColName)
{
    int offerIndex = getIndexOffer((*(Company*)data), offerId);
    if (offerIndex != -1) {
        (*(Company*)data).getOffers().at(offerIndex).setEligibility(Eligibility(atof(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), string("c++:1,java:2")));
    }
    return 0;
}

void initialize(Company& c) {
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("campusDatabase.db", &DB);
    int data = 9999;
    char* err;
    string sql("SELECT count(*) FROM Company;");
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return;
    }

    int rc = sqlite3_exec(DB, sql.c_str(), callback, &data, &err);
    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;

    if (data == 0) {
        return;
    }
    else {
        sql = "SELECT * FROM Company;";
        rc = sqlite3_exec(DB, sql.c_str(), companyCallback, &c, &err);
        sql = "Select * FROM Offer where companyId = " + to_string(c.getCompanyId());
        rc = sqlite3_exec(DB, sql.c_str(), offerCallback, &c, &err);

        for (auto it : c.getOffers()) {
            offerId = it.getOfferId();
            sql = "Select * FROM offerEligibility where offerId = " + to_string(offerId);
            rc = sqlite3_exec(DB, sql.c_str(), offerEligibilityCallback, &c, &err);
        }

        for (auto it : c.getOffers()) {

            sql = "Select * FROM College where offerId = " + to_string(it.getOfferId());
            rc = sqlite3_exec(DB, sql.c_str(), collegeCallback, &c, &err);
            if (rc != SQLITE_OK)
                cerr << "Error SELECT" << endl;

            if (data == 0) {
                return;
            }

        }

        for (auto it : c.getOffers()) {
            for (auto innerIt : it.getCollege()) {

                offerId = it.getOfferId();
                sql = "Select * FROM Student where collegeId = " + to_string(innerIt.getCollegeId());
                rc = sqlite3_exec(DB, sql.c_str(), studentCallback, &c, &err);
            }
        }

        for (auto it : c.getOffers()) {
            for (auto innerIt : it.getCollege()) {
                for (auto innerInnerIt : innerIt.getStudent()) {
                    offerId = it.getOfferId();
                    collegeId = innerIt.getCollegeId();
                    sql = "Select * FROM Eligibility where studentId = " + to_string(innerInnerIt.getID());
                    rc = sqlite3_exec(DB, sql.c_str(), studentEligibilityCallback, &c, &err);
                }
            }
        }
    }
}

int main()
{
    Company* c = new Company();
    initialize(*c);

    int userChoice;
    int companyChoice, offerChoice, collegeCode, collegeChoice, studentId, studentChoice;
    string role, location, skillName, skillLevel;
    double cgpa;
    int liveBacklog, deadBacklog, passYear, yearGap, package, bond, dd, mm, yyyy;
    string skill, collegeName, collegeEmail, collegePhone, studentName, studentEmail, studentPhoneNumber, studentDepartment;
    string companyName, companyEmail, companyPNumber, field;
    int count;
    set<int> sid;

    while (1)
    {
        cout << "\n\n************** MENU ***************"<<endl;
        cout << "Student Placement Management System" << endl;
        cout << "1-Company \n2-College\n3-Student : ";
        cin >> userChoice;
        cout << "\n\n";
        switch (userChoice)
        {
            case 1:
                cout << "1.View Company Info" << endl;
                cout << "2.Add offer" << endl;
                cout << "3.Modify Offer" << endl;
                cout << "4.View All Offers" << endl;
                cout << "5.Search Offer" << endl;
                cout << "6.Sort Offer "<<endl;
                cout << "7.View Applied students for Offer" << endl;
                cout << "8.Set Placed Students " << endl;
                cin >> companyChoice;

                switch (companyChoice)
                {

                    case 1:
                        c->display();
                        break;

                    case 2:
                        /* Add new offer */
                        cout << "\nEnter Offer Details\n";
                        cout << "\nJob Role : ";
                        cin >> role;
                        cout << "\nJob Location : ";
                        cin >> location;
                        cout << "\nPackage (CTC) : ";
                        cin >> package;
                        cout << "\nBond (Years) : ";
                        cin >> bond;
                        cout << "\nEnter Application Deadline Date : ";
                        cout << "\nEnter dd : ";
                        cin >> dd;
                        cout << "\nEnter mm : ";
                        cin >> mm;
                        cout << "\nEnter yyyy : ";
                        cin >> yyyy;

                        cout << "\nEnter Minimum CGPA : ";
                        cin >> cgpa;
                        cout << "\nEnter Live and Dead Backlog limit : ";
                        cin >> liveBacklog >> deadBacklog;
                        cout << "\nEnter Passing Year : ";
                        cin >> passYear;
                        cout << "\nEnter Year Gap : ";
                        cin >> yearGap;

                        skill = "C++:1,Java:2";

                        c->setOffer(Offer(role, location, package, bond, Date(dd, mm, yyyy), Eligibility(cgpa, liveBacklog, deadBacklog, passYear, yearGap, skill), vector<College>()), c->getName());
                        break;

                    case 3:
                        count = 0;
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "\nEnter offer index which you want Modify : ";
                        cin >> offerChoice;
                        cout << "\nPlease enter fields as below ";
                        cout << "\nJob Role -> jobRole ";
                        cout << "\nJob Location -> jobLocation";
                        cout << "\nCTC -> package";
                        cout << "\nBond -> bond\n";
                        cout << "\nEnter which field you want to Modify : \n";
                        cin >> field;
                        (c->getOffers()).at(offerChoice).setOfferId(offerChoice + 1);
                        (c->getOffers()).at(offerChoice).updateOffer(field);

                        cout << "\nData Updated Sucessfully ";
                        break;

                    case 4:
                        /* View all offers */
                        /* display offer vector after initializing from database */
                        count = 0;
                        cout << "\nIndex\tJobRole\tJobLocation " << endl;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index : ";
                        cin >> offerChoice;
                        c->getOffers().at(offerChoice).display();

                        break;

                    case 5:
                        //Search Offer
                        try {
                            string jobRole;
                            cout << "Enter Job Role which you want to Search :";
                            cin >> jobRole;
                            Offer& temp=c->search(jobRole);
                            temp.display();
                        }
                        catch (string msg) {
                            cout << msg;
                        }
                        break;

                    case 6:
                        // Sort by highest package
                        c->sort();
                        break;

                    case 7:
                        /* Shows enrolled students */
                        count = 0;
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << "\t" << endl;
                            count++;
                        }
                        cout << "Enter offer index to view applied student :";
                        cin >> offerChoice;
                        c->showAppliedStudents((offerChoice + 1));
                        break;

                    case 8:
                        count = 0;
                        int n,s;
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << "\t" << endl;
                            count++;
                        }
                        cout << "Enter offer index to set placed students :";
                        cin >> offerChoice;

                        cout << "Enter number of student placed :";
                        cin >> n;

                        for (int i = 0; i < n; i++) {
                            cout << "Enter Student Id of placed students :";
                            cin >> s;
                            sid.insert(s);
                        }

                        c->setPlacedStudents(sid, offerChoice + 1);
                        break;

                    default:
                        cout << "Invalid choice " << endl;
                        break;
                }
                break;

            case 2:
                cout << "1. Insert College Info " << endl;
                cout << "2. Modify Collge Info " << endl;
                cout << "3. Student Verification " << endl;
                cout << "4. View College info " << endl;
                cout << "5. Search Colleges " << endl;
                cout << "6. Sort Students " << endl;
                cout << "7. View Enrolled students " << endl;
                cout << "8. View placed students " << endl;
                cout << "9. Update Student Placement Status " << endl;
                cin >> collegeChoice;

                switch (collegeChoice)
                {
                    case 1:
                        /* Add college info */
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index : ";
                        cin >> offerChoice;
                        cout << "Enter College information\n";
                        cout << "Enter college name : ";
                        cin >> collegeName;
                        cout << "Enter college code : ";
                        cin >> collegeCode;
                        cout << "Enter college phone number : ";
                        cin >> collegePhone;
                        cout << "Enter college email : ";
                        cin >> collegeEmail;
                        (c->getOffers().at(offerChoice)).addCollege(College(collegeName, collegeCode, collegeEmail, collegePhone, vector<Student>()), (offerChoice + 1));

                        break;
                    case 2:
                        /* Modify college info */
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index which you want to modify :";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index which you want to modify: ";
                        cin >> collegeChoice;

                        cout << "\nEnter which field you want to Modify :";
                        cin >> field;

                        (c->getOffers().at(offerChoice)).getCollege().at(collegeChoice).setCollegeId(collegeChoice + 1);
                        (c->getOffers().at(offerChoice)).getCollege().at(collegeChoice).updateCollege(field);

                        break;

                    case 3:
                        /* Student verification */
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index :";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index : ";
                        cin >> collegeChoice;

                        (c->getOffers().at(offerChoice)).getCollege().at(collegeChoice).verifyStudent();
                        break;

                    case 4:
                        /* View college info */
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index :";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index : ";
                        cin >> collegeChoice;
                        (c->getOffers()).at(offerChoice).getCollege().at(collegeChoice).display();
                        break;

                    case 5:
                        try {
                            cout << "\nIndex\tJobRole\tJobLocation" << endl;
                            count = 0;
                            for (auto it : c->getOffers())
                            {
                                cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                                count++;
                            }
                            cout << "Enter offer index :";
                            cin >> offerChoice;

                            string collegeName;
                            cout << "Enter college Name which you want to Search :";
                            cin >> collegeName;
                            College& temp = c->getOffers().at(offerChoice).search(collegeName);
                            temp.display();
                        }
                        catch (string msg) {
                            cout << msg;
                        }
                        break;

                    case 6:
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index :";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index : ";
                        cin >> collegeChoice;

                        (c->getOffers()).at(offerChoice).getCollege().at(collegeChoice).sort(collegeChoice+1);

                        break;

                    case 7:
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index :";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index : ";

                        cin >> collegeChoice;

                        cout << "\nEnrolled students in College are follows :"<<endl;
                        (c->getOffers()).at(offerChoice).getCollege().at(collegeChoice).viewEnrolledStudents();
                        break;

                    case 8:
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index :";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCollegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index : ";
                        cin >> collegeChoice;
                        cout << "\nPlaced students in College are follows :" << endl;
                        (c->getOffers()).at(offerChoice).getCollege().at(collegeChoice).viewPlacedStudents();
                        break;

                    case 9:
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index :";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index : ";
                        cin >> collegeChoice;
                        (c->getOffers()).at(offerChoice).getCollege().at(collegeChoice).updateStudentPlacedStatus();

                        break;

                    default:
                        cout << "Invalid choice " << endl;
                        break;
                }
                break;

            case 3:
                cout << "1. Insert " << endl;
                cout << "2. Modify " << endl;
                cout << "3. View Student Information " << endl;
                cout << "4. Add Skills " << endl;
                cout << "5. Apply for offers " << endl;

                cin >> studentChoice;

                switch (studentChoice)
                {
                    case 1: /*Add student data function call*/
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index : ";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index : ";
                        cin >> collegeChoice;
                        cout << "Enter student information\n";
                        cout << "Enter student id : ";
                        cin >> studentId;
                        cout << "Enter student name : ";
                        cin >> studentName;
                        cout << "Enter student email : ";
                        cin >> studentEmail;
                        cout << "Enter student phone number : ";
                        cin >> studentPhoneNumber;
                        cout << "Enter student DOB : ";
                        cout << "\nEnter dd ";
                        cout << "\nEnter mm ";
                        cout << "\nEnter yyyy ";
                        cin >> dd >> mm >> yyyy;
                        cout << "Enter student department : ";
                        cin >> studentDepartment;
                        cout << "Enter student cgpa\n";
                        cin >> cgpa;
                        cout << "Enter live and dead backlogs : ";
                        cin >> liveBacklog >> deadBacklog;
                        cout << "Enter passing year and student year gap : ";
                        cin >> passYear >> yearGap;
                        skill = "c++:1,java:2";
                        c->getOffers().at(offerChoice).getCollege().at(collegeChoice).
                            addStudent(Student(studentName, studentId, studentEmail, studentPhoneNumber,
                                        Date(dd, mm, yyyy), studentDepartment, Eligibility(cgpa, liveBacklog, deadBacklog,
                                            passYear, yearGap, skill)), collegeChoice + 1);
                        break;

                    case 2: /*Update data function call*/
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "\nEnter offer index which you want to modify: ";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCollegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "\nEnter college index which you want to modify: ";
                        cin >> collegeChoice;

                        cout << "\nIndex\tStudentId\tStudentName" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                        {
                            cout << count << "\t" << it.getID() << "\t" <<it.getName() << endl;
                            count++;
                        }
                        cout << "\nEnter student index which you want to modify:";
                        cin >> studentChoice;

                        cout << "\nEnter fields as follows ";
                        cout << "\nName -> studentName ";
                        cout << "\nPhone Number -> studentPhoneNumber";
                        cout << "\nEmail -> studentEmail";
                        cout << "\nDepartment -> studentDepartment\n";
                        cout << "\nEnter which field you want to Modify :";
                        cin >> field;
                        c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).setID(studentChoice + 1);
                        c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).updateStudent(field);
                        break;

                    case 3://Display
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index : ";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index : ";
                        cin >> collegeChoice;

                        cout << "\nIndex\tStudentId\tStudentName" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                        {
                            cout << count << "\t" << it.getID() << "\t" << it.getName() <<endl;
                            count++;
                        }
                        cout << "Enter student index\n";
                        cin >> studentChoice;
                        c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).display();

                        break;

                    case 4:
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index : ";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                        }
                        cout << "Enter college index : ";
                        cin >> collegeChoice;

                        cout << "\nIndex\tStudentId\tStudentName" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                        {
                            cout << count << "\t" << it.getID() << "\t" << it.getName() << endl;
                        }
                        cout << "Enter student index : ";
                        cin >> studentChoice;
                        cout << "Enter skill name : ";
                        cin >> skillName;
                        cout << "Enter skill expertise level (1 - beginer, 2 - intermediate, 3 - advanced) : ";
                        cin >> skillLevel;
                        c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).getAcademicDetails().addSkill(skillName, skillLevel);

                        break;

                    case 5:
                        cout << "\nIndex\tJobRole\tJobLocation" << endl;
                        count = 0;
                        for (auto it : c->getOffers())
                        {
                            cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                            count++;
                        }
                        cout << "Enter offer index : ";
                        cin >> offerChoice;

                        cout << "\nIndex\tCollegeName\tCOllegeCode" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege())
                        {
                            cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                            count++;
                        }
                        cout << "Enter college index : ";
                        cin >> collegeChoice;

                        cout << "\nIndex\tStudentId\tStudentName" << endl;
                        count = 0;
                        for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                        {
                            cout << count << "\t" << it.getID() << "\t" << it.getName() << endl;
                            count++;
                        }
                        cout << "Enter student index : ";
                        cin >> studentChoice;

                        c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).applyForCompany((offerChoice+1));
                        break;

                    default:
                        cout << "Invalid choice " << endl;
                        break;
                }
                break;

            default:
                cout << "Invalid choice " << endl;
                break;
        }
    }

    delete c;
}

// End of file
