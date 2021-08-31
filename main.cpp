#include <iostream>
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
/*
static int callback(void* data, int argc, char** argv, char** azColName)
{
	//fprintf(stderr, "%s: ", (const char*)data);

	cout << "in call back\n";
		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	Eligibility* tempCriteria = new Eligibility(atof(argv[1]), atoi(argv[2]), atoi(argv[3]), 2021, atoi(argv[4]), string("cpp:1,java:2"));
	Eligibility* studentAcademicDetails = new Eligibility(8.5, 0, 0, 2021, 0, string("cpp:1,java:2"));
	cout << tempCriteria->getLiveBackLog() << "\n";
	if (*(studentAcademicDetails) == *(tempCriteria)) {
		(*(vector<int>*)data).push_back(atoi(argv[0]));
		cout << "inside if\n";
	}

	delete studentAcademicDetails;
	delete tempCriteria;
	printf("\n");
	return 0;
}
int main(int argc, char** argv)
{
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("campus.db", &DB);
	//string data("CALLBACK FUNCTION");
	vector<int> data;
	string sql("select CO.id, CA.cgpa, CA.liveBacklog, CA.deadBacklog,CA.yearGap from Company_offer as CO inner join Company_criteria as CA on CO.id = CA.offerId_id;");
	if (exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return (-1);
	}
	else
		std::cout << "Opened Database Successfully!" << std::endl;

	int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)&data, NULL);
	for (auto it : data) {
		cout << it << "\n";;
	}
	if (rc != SQLITE_OK)
		cerr << "Error SELECT" << endl;
	else {
		cout << "Operation OK!" << endl;
	}

	sqlite3_close(DB);
	return (0);
}




using namespace std;

int main() {
	Eligibility studentAcademicDetails(8.5, 0, 0, 2021, 0, string("cpp:1,java:2"));
	Student s("abc", 101, "a@b", "lmn", Date(10, 10, 10), "xyz", studentAcademicDetails);
	vector<int> off = s.getApplicableOffers();
	s.apply(off[0]);
	return 0;
}

*/

int main()
{
    Company *c = new Company("Persistent", "ps@.com", "12345567", vector<Offer>());

    //(c->getOffers().at(0)).addCollege(College("SCOE", 4023, "sc@.com", "1234566", vector<Student>()));
    //(c->getOffers().at(0)).addCollege(College());
    //cout << c->getOffers()[0].getCollege()[0].getName();
    //(c->getOffers().at(0)).getCollege().at(0).addStudent(Student("name", 101, "st@.com", "1234567", Date(1, 1, 1), "CS", Eligibility()));
    //cout << (c->getOffers().at(0)).getCollege().at(0).getStudent().at(0).getName();

    int choice;
    int companyChoice, offerChoice, collegeCode, collegeChoice, studentId, studentChoice;
    string role, location, skillName, skillLevel;
    double cgpa;
    int liveBacklog, deadBacklog, passYear, yearGap, package, bond, dd, mm, yyyy;
    string skill, collegeName, collegeEmail, collegePhone, studentName, studentEmail, studentPhoneNumber, studentDepartment;

    while(1)
    {
        cout << "====" << endl;
        cout << "Student Placement Management System" << endl;
        cout << "1-Company \n2-Offer Menu\n3-College \n4-Student\n\n" ;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "1-View Company Info \n2-Add new Offer\n";
            cin >> companyChoice;
            if (companyChoice == 1)
            {
                c->display();
            }
            else if (companyChoice == 2)
            {
                cout << "Enter Offer Details\n";
                cout << "Job Role : \n";
                cin >> role;
                cout << "Job Location : \n";
                cin >> location;
                cout << "Package (CTC) : \n";
                cin >> package;
                cout << "Bond (Years) : ";
                cin >> bond;
                cout << "Enter Application Deadline Date: ";
                cout << "Enter dd "; cin >> dd;
                cout << "Enter mm "; cin >> mm;
                cout << "Enter yyyy "; cin >> yyyy;

                cout << "Enter Minimum CGPA \n";
                cin >> cgpa;
                cout << "Enter Live and Dead Backlog limit \n";
                cin >> liveBacklog >> deadBacklog;
                cout << "Enter Passing Year \n";
                cin >> passYear;
                cout << "Enter Year Gap \n";
                cin >> yearGap;

                skill = "C++:1,Java:2";
                c->setOffer(Offer(role, location, package, bond, Date(dd, mm, yyyy), Eligibility(cgpa, liveBacklog, deadBacklog, passYear, yearGap, skill), vector<College>()), );
            }
            break;
        case 2:
            cout << "\n1-Display Offer Details \n2-Add College\n";
            cin >> offerChoice;
            if (offerChoice == 1)
            {
                int count = 0;
                for (auto it : c->getOffers())
                {
                    cout << it.getJobRole() << endl;
                    cout << it.getJobLocation() << endl;
                    cout << count << endl;
                    count++;
                }
                cout << "Enter Offer Index: \n";
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
                cout << "Enter Offer Index : \n";
                cin >> offerChoice;
                cout << "Enter College Information\n";
                cout << "Enter College Name : \n";
                cin >> collegeName;
                cout << "enter college code : \n";
                cin >> collegeCode;
                cout << "enter college phone number : ";
                cin >> collegePhone;
                cout << "enter college email : ";
                cin >> collegeEmail;
                (c->getOffers().at(offerChoice)).addCollege(College(collegeName, collegeCode, collegeEmail, collegePhone, vector<Student>()));
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
                cout << "Enter College Index : ";
                cin >> collegeChoice;
                cout << "Enter Student Information\n";
                cout << "Enter Student Name : ";
                cin >> studentName;
                cout << "Enter Student Id : ";
                cin >> studentId;
                cout << "Enter Student Email : ";
                cin >> studentEmail;
                cout << "Enter Student Phone Number : ";
                cin >> studentPhoneNumber;
                cout << "Enter Student DOB(dd/mm/yyyy) : ";
                cin >> dd >> mm >> yyyy;
                cout << "Enter student department : ";
                cin >> studentDepartment;
                cout << "Enter student cgpa\n";
                cin >> cgpa;
                cout << "Enter live and dead backlogs : \n";
                cin >> liveBacklog >> deadBacklog;
                cout << "Enter passing year and student year gap : \n";
                cin >> passYear >> yearGap;
                skill = "c++:1,java:2";
                c->getOffers().at(offerChoice).getCollege().at(collegeChoice).addStudent(Student(studentName, studentId, studentEmail, studentPhoneNumber, Date(dd, mm, yyyy), studentDepartment, Eligibility(cgpa, liveBacklog, deadBacklog, passYear, yearGap, skill)));
            }
            break;
        case 4:
            cout << "1-View Student Information\n2 - add skill\n";
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

        cout << "Do you want to continue ? " << endl;
    }
    return 0;
}

/*

Common
    1. Display all data
Student
    1. Display academic details
    2. Enter student data
    3. Show applicable offers
    4. Apply for offer

College
    1. Enter college information
    2. Add student
    3. View enrolled students
    4. Update student placement status from temporary table to college database

Company
    1. Enter company information
    2. Add offers
    3. Show current offers
    4. Send recruited student list to college for respective offer
    5. Show applied students for their offer

*/

/*

Azure
1. Security - policy and roles
2. Compute - Create EC2 instances && deployment
3. Elastic load balancer -> Autoscaling -
4. DNS
5. Storage - Bucket/DB

*/
