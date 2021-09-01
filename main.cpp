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
using namespace std;


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
    cout << "in callback";
    int i;
    *(int*)data = atoi(argv[0]);
    cout << argv[0] << endl;
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
    (*(Company*)data).setOffer(Offer(atoi(argv[0]), argv[3], argv[2], atof(argv[1]), atof(argv[5]), Date(1, 1, 1), Eligibility(), vector<College>()));
    cout << argv[0];
    return 0;
}

static int collegeCallback(void* data, int argc, char** argv, char** azColName)
{
    int offerIndex = getIndexOffer((*(Company*)data), atoi(argv[4]));
    cout << "OfferIndex :"<<offerIndex;
    (*(Company*)data).getOffers().at(offerIndex).addCollege(College(atoi(argv[0]), argv[1], atoi(argv[5]), argv[3], argv[2], vector<Student>()));
    return 0;
}

int offerId, collegeId;
static int studentCallback(void* data, int argc, char** argv, char** azColName)
{
    cout << "in student call back offerId : " << offerId << endl;
    int offerIndex = getIndexOffer((*(Company*)data), offerId);
    int collegeIndex = getIndexCollege((*(Company*)data), offerId, atoi(argv[7]));
    cout << "College Index : " << collegeIndex << endl;
    if (collegeIndex != -1) {
        (*(Company*)data).getOffers().at(offerIndex).getCollege().at(collegeIndex).addStudent(Student(argv[1], atoi(argv[0]), argv[3], argv[4], Date(4, 4, 4), argv[5], Eligibility()));
    }
    return 0;
}

static int studentEligibilityCallback(void* data, int argc, char** argv, char** azColName)
{
    cout << "in student call back offerId : " << offerId << endl;
    int offerIndex = getIndexOffer((*(Company*)data), offerId);
    int collegeIndex = getIndexCollege((*(Company*)data), offerId, collegeId);
    int studentIndex = getIndexStudent((*(Company*)data), offerId, collegeId, atoi(argv[6]));
    cout << "College Index : " << collegeIndex << endl;
    cout << "student index : " << studentIndex << endl;
    cout << "py : " << atoi(argv[4]) << endl;
    if (studentIndex != -1) {
        (*(Company*)data).getOffers().at(offerIndex).getCollege().at(collegeIndex).getStudent().at(studentIndex).setAcademicDetails(Eligibility(atof(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), string("c++:1,java:2")));
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
    else
        std::cout << "Opened Database Successfully!" << std::endl;
    int rc = sqlite3_exec(DB, sql.c_str(), callback, &data, &err);
    //cout << err;
    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;
    else {
        cout << "Operation OK!" << endl;
    } if (data == 0) {
        return;
    }
    else {
        sql = "SELECT * FROM Company;";
        rc = sqlite3_exec(DB, sql.c_str(), companyCallback, &c, &err);
        cout << c.getEmail();
        c.display();
        sql = "Select * FROM Offer where companyId = " + to_string(c.getCompanyId());
        rc = sqlite3_exec(DB, sql.c_str(), offerCallback, &c, &err);
        c.display();
        cout << "==================================\n";
        for (auto it : c.getOffers()) {
            cout << "offer id : " << it.getOfferId() << endl;
            cout << "job Role : " << it.getJobRole() << endl;
            cout << "JobLocation : " << it.getJobLocation() << endl;

            sql = "Select * FROM College where offerId = " + to_string(it.getOfferId());
            rc = sqlite3_exec(DB, sql.c_str(), collegeCallback, &c, &err);
            if (rc != SQLITE_OK)
                cerr << "Error SELECT" << endl;
            else {
                cout << "Operation OK!" << endl;
            } if (data == 0) {
                return;
            }


        }
        for (auto it : c.getOffers()) {
            it.display();
        }
        cout << "===================================\n";
        for (auto it : c.getOffers()) {
            for (auto innerIt : it.getCollege()) {
                innerIt.display();
                offerId = it.getOfferId();
                cout << "offer index : " << offerId << endl;
                cout << "offer index : " << getIndexOffer(c, offerId);
                cout << "College id : " << innerIt.getCollegeId() << endl;
                sql = "Select * FROM Student where collegeId = " + to_string(innerIt.getCollegeId());
                rc = sqlite3_exec(DB, sql.c_str(), studentCallback, &c, &err);
            }
        }
        cout << "===================================\n";
        cout << "Student" << endl;
        cout << "===================================\n";
        for (auto it : c.getOffers()) {
            for (auto innerIt : it.getCollege()) {
                for (auto innerInnerIt : innerIt.getStudent()) {
                    innerInnerIt.display();
                }
            }
        }
        /*
        */
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
        cout << "===================================\n==================================\n";
        for (auto it : c.getOffers()) {
            for (auto innerIt : it.getCollege()) {
                for (auto innerInnerIt : innerIt.getStudent()) {
                    innerInnerIt.display();
                }
            }
        }
    }
}






int main()
{
//    Company* c=new Company("PSL", "PSL@gmail.com","123456789", vector<Offer>());
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

    while (1)
    {
        cout << "===" << endl;
        cout << "Student Placement Management System" << endl;
        cout << "1-Company \n2-College\n3-Student \n\n";
        cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            cout << "1.View Company Info" << endl;
            cout << "2.Add offer" << endl;
            cout << "3.Modify Offer" << endl;
            cout << "4.View All Offers" << endl;
            cout << "5.Search Offer" << endl;
            cout << "6.View enrolled students" << endl;
            cin >> companyChoice;

            switch (companyChoice)
            {

            case 1:
                c->display();
                break;

            case 2:
                /* Add new offer */
                cout << "Enter Offer Details";
                cout << "\nJob Role :";
                cin >> role;
                cout << "Job Location :";
                cin >> location;
                cout << "Package (CTC) :";
                cin >> package;
                cout << "Bond (Years) :";
                cin >> bond;
                cout << "Enter Application Deadline Date :";
                cout << "Enter dd :";
                cin >> dd;
                cout << "Enter mm :";
                cin >> mm;
                cout << "Enter yyyy :";
                cin >> yyyy;

                cout << "Enter Minimum CGPA :";
                cin >> cgpa;
                cout << "Enter Live and Dead Backlog limit :";
                cin >> liveBacklog >> deadBacklog;
                cout << "Enter Passing Year :";
                cin >> passYear;
                cout << "Enter Year Gap :";
                cin >> yearGap;

                skill = "C++:1,Java:2";

                c->setOffer(Offer(role, location, package, bond, Date(dd, mm, yyyy), Eligibility(cgpa, liveBacklog, deadBacklog, passYear, yearGap, skill), vector<College>()), c->getName());
                break;

            case 3:
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << "\t" << endl;
                    count++;
                }
                cout << "Enter offer index which you want Modify :";
                cin >> offerChoice;
                cout << "\nEnter which field you want to Modify :";
                cin >> field;
                (c->getOffers()).at(offerChoice).setOfferId(offerChoice + 1);
                (c->getOffers()).at(offerChoice).updateOffer(field);

                cout << "\nData Updated Sucessfully";
                break;

            case 4:
                /* View all offers */
                /* display offer vector after initializing from database */
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << "\t" << endl;
                    count++;
                }
                cout << "Enter offer index :";
                cin >> offerChoice;
                c->getOffers().at(offerChoice).display();

                break;

            case 5:
                //Search Offer
                break;

            case 6:
                /* Shows enrolled students */
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << "\t" << endl;
                    count++;
                }
                cout << "Enter offer index to view applied student :";
                cin >> offerChoice;
                c->showAppliedStudents((offerChoice + 1));
                break;

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
            cout << "6. View Enrolled students " << endl;
            cout << "7. View placed students " << endl;
            cin >> collegeChoice;

            switch (collegeChoice)
            {
            case 1:
                /* Add college info */
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                    count++;
                }
                cout << "Enter offer index : ";
                cin >> offerChoice;
                cout << "Enter College information\n";
                cout << "enter college name : ";
                cin >> collegeName;
                cout << "enter college code : ";
                cin >> collegeCode;
                cout << "enter college phone number : ";
                cin >> collegePhone;
                cout << "enter college email : ";
                cin >> collegeEmail;
                (c->getOffers().at(offerChoice)).addCollege(College(collegeName, collegeCode, collegeEmail, collegePhone, vector<Student>()), (offerChoice + 1));

                break;
            case 2:
                /* Modify college info */
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                    count++;
                }
                cout << "Enter offer index which you want to modify :";
                cin >> offerChoice;
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
                (c->getOffers().at(offerChoice)).getCollege().at(collegeChoice).verifyStudent();
                break;

            case 4:
                /* View college info */

                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                    count++;
                }
                cout << "Enter offer index :";
                cin >> offerChoice;
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
                /* Search College */
                break;

            case 6:
                (c->getOffers()).at(offerChoice).getCollege().at(collegeChoice).viewEnrolledStudents();
                break;

            case 8:
                (c->getOffers()).at(offerChoice).getCollege().at(collegeChoice).viewPlacedStudents();
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
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                    count++;
                }
                cout << "Enter offer index : ";
                cin >> offerChoice;
                count = 0;
                for (auto it : c->getOffers().at(offerChoice).getCollege())
                {
                    cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                    count++;
                }
                cout << "enter college index : ";
                cin >> collegeChoice;
                cout << "enter student information\n";
                cout << "enter student id : ";
                cin >> studentId;
                cout << "enter student name : ";
                cin >> studentName;
                cout << "enter student email : ";
                cin >> studentEmail;
                cout << "enter student phone number : ";
                cin >> studentPhoneNumber;
                cout << "enter student DOB(dd/mm/yyyy) : ";
                cin >> dd >> mm >> yyyy;
                cout << "enter student department : ";
                cin >> studentDepartment;
                cout << "enter student cgpa\n";
                cin >> cgpa;
                cout << "enter live and dead backlogs : ";
                cin >> liveBacklog >> deadBacklog;
                cout << "enter passing year and student year gap : ";
                cin >> passYear >> yearGap;
                skill = "c++:1,java:2";
                c->getOffers().at(offerChoice).getCollege().at(collegeChoice).
                    addStudent(Student(studentName, studentId, studentEmail, studentPhoneNumber,
                        Date(dd, mm, yyyy), studentDepartment, Eligibility(cgpa, liveBacklog, deadBacklog,
                            passYear, yearGap, skill)), collegeChoice + 1);
                break;

            case 2: /*Update data function call*/
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                    count++;
                }
                cout << "\nEnter offer index which you want to modify: ";
                cin >> offerChoice;
                count = 0;
                for (auto it : c->getOffers().at(offerChoice).getCollege())
                {
                    cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                    count++;
                }
                cout << "\nEnter college index which you want to modify: ";
                cin >> collegeChoice;
                count = 0;
                for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                {
                    cout << count << "\t" << it.getID() << endl;
                    count++;
                }
                cout << "\nEnter student index which you want to modify:";
                cin >> studentChoice;

                cout << "\nEnter which field you want to Modify :";
                cin >> field;
                c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).setID(studentChoice + 1);
                c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).updateStudent(field);
                break;

            case 3://Display
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << count << "\t" << it.getJobRole() << "\t" << it.getJobLocation() << endl;
                    count++;
                }
                cout << "enter offer index : ";
                cin >> offerChoice;
                count = 0;
                for (auto it : c->getOffers().at(offerChoice).getCollege())
                {
                    cout << count << "\t" << it.getName() << "\t" << it.getCollegeCode() << endl;
                    count++;
                }
                cout << "enter college index : ";
                cin >> collegeChoice;
                count = 0;
                for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                {
                    cout << count << "\t" << it.getID() << endl;
                    count++;
                }
                cout << "enter student index\n";
                cin >> studentChoice;
                c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).display();

                break;

            case 4:
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << it.getJobRole() << endl;
                    cout << it.getJobLocation() << endl;
                    cout << count << endl;
                    count++;
                }
                cout << "Enter offer index : ";
                cin >> offerChoice;
                count = 0;
                for (auto it : c->getOffers().at(offerChoice).getCollege())
                {
                    cout << it.getName() << endl;
                    cout << it.getCollegeCode() << endl;
                    cout << count << endl;
                    count++;
                }
                cout << "Enter college index : ";
                cin >> collegeChoice;
                count = 0;
                for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                {
                    cout << it.getID() << endl;
                    cout << count << endl;
                    count++;
                }
                cout << "Enter student index\n";
                cin >> studentChoice;
                cout << "Enter skill name : ";
                cin >> skillName;
                cout << "Enter skill expertise level (1 - beginer, 2 - intermediate, 3 - advanced) : ";
                cin >> skillLevel;
                c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).getAcademicDetails().addSkill(skillName, skillLevel);

                break;

            case 5:
                count = 0;
                for (auto it : c->getOffers())
                {
                    cout << it.getJobRole() << endl;
                    cout << it.getJobLocation() << endl;
                    cout << count << endl;
                    count++;
                }
                cout << "Enter offer index : ";
                cin >> offerChoice;
                count = 0;
                for (auto it : c->getOffers().at(offerChoice).getCollege())
                {
                    cout << it.getName() << endl;
                    cout << it.getCollegeCode() << endl;
                    cout << count << endl;
                    count++;
                }
                cout << "Enter college index : ";
                cin >> collegeChoice;
                count = 0;
                for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                {
                    cout << it.getID() << endl;
                    cout << count << endl;
                    count++;
                }
                cout << "Enter student index\n";
                cin >> studentChoice;

                c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).applyForCompany((offerChoice+1));


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
}






        /*
        cout << " Student Placement Management System" << endl;
        cout << "1-Company \n2-Offer Menu\n3-College \n4-Student\n";
        cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "1-View Company Information, 2 - add offer\n";
                cin >> companyChoice;
                if (companyChoice == 1)
                {
                    c->display();
                }
                else if (companyChoice == 2)
                {
                    cout << "enter offer information\n";
                    cout << "enter job role : ";
                    cin >> role;
                    cout << "enter job location : ";
                    cin >> location;
                    cout << "enter package : ";
                    cin >> package;
                    cout << "enter bond : ";
                    cin >> bond;
                    cout << "enter last date to apply(dd/mm/yyyy) : ";
                    cin >> dd >> mm >> yyyy;
                    cout << "enter required cgpa\n";
                    cin >> cgpa;
                    cout << "enter live and dead backlogs : ";
                    cin >> liveBacklog >> deadBacklog;
                    cout << "enter passing year and acceptable year gap : ";
                    cin >> passYear >> yearGap;
                    skill = "c++:1,java:2";
                    string cName = c->getName();
                    c->setOffer(Offer(role, location, package, bond, Date(dd, mm, yyyy), Eligibility(cgpa, liveBacklog, deadBacklog, passYear, yearGap, skill), vector<College>()),cName);
                }
                break;
            case 2:
                cout << "1 - display details of offer, 2 - add college\n";
                cin >> offerChoice;
                if (offerChoice == 1)
                {
                    int count = 0;
                    for (auto it : c->getOffers())
                    {
                        cout << it.getJobRole() << "\t" << it.getJobLocation() << "\t" << count << endl;
                        count++;
                    }
                    cout << "enter offer index : ";
                    cin >> offerChoice;
                    c->getOffers().at(offerChoice).display();
                }
                else if (offerChoice == 2)
                {
                    int count = 0;
                    for (auto it : c->getOffers())
                    {
                        cout << it.getJobRole() << endl;
                        cout << it.getJobLocation() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter offer index : ";
                    cin >> offerChoice;
                    cout << "Enter College information\n";
                    cout << "enter college name : ";
                    cin >> collegeName;
                    cout << "enter college code : ";
                    cin >> collegeCode;
                    cout << "enter college phone number : ";
                    cin >> collegePhone;
                    cout << "enter college email : ";
                    cin >> collegeEmail;
                    (c->getOffers().at(offerChoice)).addCollege(College(collegeName, collegeCode, collegeEmail, collegePhone, vector<Student>()),(offerChoice+1));
                }
                break;
            case 3:
                cout << "1 - view college information, 2 - add student\n";
                cin >> collegeChoice;
                if (collegeChoice == 1)
                {
                    int count = 0;
                    for (auto it : c->getOffers())
                    {
                        cout << it.getJobRole() << endl;
                        cout << it.getJobLocation() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter offer index : ";
                    cin >> offerChoice;
                    count = 0;
                    for (auto it : c->getOffers().at(offerChoice).getCollege())
                    {
                        cout << it.getName() << endl;
                        cout << it.getCollegeCode() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter college index : ";

                    cin >> collegeChoice;
                    c->getOffers().at(offerChoice).getCollege().at(collegeChoice).display();
                }
                else if (collegeChoice == 2)
                {
                    int count = 0;
                    for (auto it : c->getOffers())
                    {
                        cout << it.getJobRole() << endl;
                        cout << it.getJobLocation() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter offer index : ";
                    cin >> offerChoice;
                    count = 0;
                    for (auto it : c->getOffers().at(offerChoice).getCollege())
                    {
                        cout << it.getName() << endl;
                        cout << it.getCollegeCode() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter college index : ";
                    cin >> collegeChoice;
                    cout << "enter student information\n";
                    cout << "enter student name : ";
                    cin >> studentName;
                    cout << "enter student id : ";
                    cin >> studentId;
                    cout << "enter student email : ";
                    cin >> studentEmail;
                    cout << "enter student phone number : ";
                    cin >> studentPhoneNumber;
                    cout << "enter student DOB(dd/mm/yyyy) : ";
                    cin >> dd >> mm >> yyyy;
                    cout << "enter student department : ";
                    cin >> studentDepartment;
                    cout << "enter student cgpa\n";
                    cin >> cgpa;
                        cout << "enter live and dead backlogs : ";
                    cin >> liveBacklog >> deadBacklog;
                    cout << "enter passing year and student year gap : ";
                    cin >> passYear >> yearGap;
                    skill = "c++:1,java:2";
                    c->getOffers().at(offerChoice).getCollege().at(collegeChoice).
                    addStudent(Student(studentName, studentId, studentEmail, studentPhoneNumber,
                    Date(dd, mm, yyyy), studentDepartment, Eligibility(cgpa, liveBacklog, deadBacklog,
                        passYear, yearGap, skill)),collegeChoice+1);
                }
                break;
            case 4:
                cout << "1 - view student information, 2 - add skill\n";
                cin >> studentChoice;
                if (studentChoice == 1)
                {
                    int count = 0;
                    for (auto it : c->getOffers())
                    {
                        cout << it.getJobRole() << endl;
                        cout << it.getJobLocation() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter offer index : ";
                    cin >> offerChoice;
                    count = 0;
                    for (auto it : c->getOffers().at(offerChoice).getCollege())
                    {
                        cout << it.getName() << endl;
                        cout << it.getCollegeCode() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter college index : ";
                    cin >> collegeChoice;
                    count = 0;
                    for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                    {
                        cout << it.getID() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter student index\n";
                    cin >> studentChoice;
                    c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).display();
                }
                else if (studentChoice == 2)
                {
                    int count = 0;
                    for (auto it : c->getOffers())
                    {
                        cout << it.getJobRole() << endl;
                        cout << it.getJobLocation() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter offer index : ";
                    cin >> offerChoice;
                    count = 0;
                    for (auto it : c->getOffers().at(offerChoice).getCollege())
                    {
                        cout << it.getName() << endl;
                        cout << it.getCollegeCode() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter college index : ";
                    cin >> collegeChoice;
                    count = 0;
                    for (auto it : c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent())
                    {
                        cout << it.getID() << endl;
                        cout << count << endl;
                        count++;
                    }
                    cout << "enter student index\n";
                    cin >> studentChoice;
                    cout << "enter skill name : ";
                    cin >> skillName;
                    cout << "enter skill expertise level (1 - beginer, 2 - intermediate, 3 - advanced) : ";
                    cin >> skillLevel;
                    c->getOffers().at(offerChoice).getCollege().at(collegeChoice).getStudent().at(studentChoice).getAcademicDetails().addSkill(skillName, skillLevel);
                }
                break;
            default:
                break;
            }
    }
    return 0;
}
*/
