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

int main()
{
    Company *c = new Company("Persistent", "ps@email.com", "123123123", vector<Offer>());

    int userChoice, companyChoice, collegeChoice, studentChoice;

    int studentId;
    string role, location, skillName, skillLevel;
    double cgpa;
    int liveBacklog, deadBacklog, passYear, yearGap, package, bond, dd, mm, yyyy;
    string skill, collegeName, collegeEmail, collegePhone, studentName, studentEmail, studentPhoneNumber, studentDepartment;

    while (1)
    {
        cout << "===" << endl;
        cout << "Student Placement Management System" << endl;
        cout << "1-Company \n2-College\n3-Student \n\n";
        cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            cout << "1.Add Company Info" << endl;
            cout << "2.Modify Company Info" << endl;
            cout << "3.View Company Info" << endl;
            cout << "4.View enrolled students" << endl;
            cout << "5.Add offer" << endl;
            cout << "6.Modify Offer" << endl;
            cout << "7.View All Offers" << endl;
            cout << "8.Search Offer" << endl;
            cin >> companyChoice;

            switch (companyChoice)
            {
            case 1:
                /* Add company info */
                break;
            case 2:
                /* Modify company info */
                break;
            case 3:
                /* Displays company info */
                c->display();
                break;
            case 4:
                /* Shows enrolled students */
                c->showAppliedStudents(int);
                break;
            case 5:
                /* Add new offer */
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
                cout << "Enter dd ";
                cin >> dd;
                cout << "Enter mm ";
                cin >> mm;
                cout << "Enter yyyy ";
                cin >> yyyy;

                cout << "Enter Minimum CGPA \n";
                cin >> cgpa;
                cout << "Enter Live and Dead Backlog limit \n";
                cin >> liveBacklog >> deadBacklog;
                cout << "Enter Passing Year \n";
                cin >> passYear;
                cout << "Enter Year Gap \n";
                cin >> yearGap;

                skill = "C++:1,Java:2";

                c->setOffer(Offer(role, location, package, bond, Date(dd, mm, yyyy), Eligibility(cgpa, liveBacklog, deadBacklog, passYear, yearGap, skill), vector<College>()));
                break;
            case 6:
                /* Modify offer */
                break;
            case 7:
                /* View all offers */
                /* display offer vector after initializing from database */
                break;
            case 8:
                // search offer
                break;
            default:
                cout << "Invalid choice " << endl;
                break;
            }
            break;

        case 2:
            cout << "1. Insert " << endl;
            cout << "2. Modify " << endl;
            cout << "3. Student Verification " << endl;
            cout << "4. Company Verification " << endl;
            cout << "5. View College info " << endl;
            cout << "6. Search Colleges " << endl;
            cout << "7. View Enrolled students " << endl;
            cout << "8. View placed students " << endl;
            cin >> collegeChoice;

            switch (collegeChoice)
            {
            case 1:
                /* Add college info */
                break;
            case 2:
                /* Modify college info */
                break;
            case 3:
                /* Student verification */
                break;
            case 4:
                /* Company verification */
                break;
            case 5:
                /* View college info */
                break;
            case 6:
                /* Search College */
                break;
            case 7:
                /* view enrolled students */
                break;
            case 8:
                /* view placed students */
                break;
            default:
                cout << "Invalid choice " << endl;
                break;
            }
            break;
        }

        break;

    case 3:
        cout << "1. Insert " << endl;
        cout << "2. Modify " << endl;
        cout << "3. Send for verification " << endl;
        cout << "4. View eligible offers " << endl;
        cout << "5. Apply for offers " << endl;
        break;

        switch (studentChoice)
        {
        case 1: /*Add student data function call*/
            break;

        case 2: /*Update data function call*/
            break;

        case 3: 
            /*send data for verification?*/
            cout << "Sent for verification" ;
            break;

        case 4: /*view offers function call*/
            break;

        case 5: /*Apply for offers*/
            break;

        default:
            cout << "Invalid choice " << endl;
            break;
        }

    default:
        cout << "Invalid choice " << endl;
        break;
    }
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
