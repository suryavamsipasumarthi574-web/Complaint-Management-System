#include <iostream>
#include <string>
#include <limits>

using namespace std;


// ==========================================
// PHONE NUMBER VALIDATION
// ==========================================

bool validPhone(const string& phone)
{
    // Check exactly 10 digits
    if (phone.length() != 10)
    {
        return false;
    }

    // Check whether all characters are digits
    // C++98 compatible loop
    for (int i = 0; i < phone.length(); i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            return false;
        }
    }

    return true;
}


// ==========================================
// COMPLAINT CLASS
// ==========================================

class Complaint
{
private:

    int id;
    string name;
    string phone;
    string problem;
    string status;


public:

    // ======================================
    // DEFAULT CONSTRUCTOR
    // ======================================

    Complaint()
    {
        id = 0;
        name = "";
        phone = "";
        problem = "";
        status = "Pending";
    }


    // ======================================
    // REGISTER COMPLAINT
    // ======================================

    void registerComplaint(int newId)
    {
        id = newId;

        cout << "\n========== REGISTER COMPLAINT ==========\n";

        cout << "Enter Name : ";
        cin >> name;


        // ----------------------------------
        // PHONE NUMBER VALIDATION
        // ----------------------------------

        do
        {
            cout << "Enter Phone (10 digits) : ";
            cin >> phone;

            if (!validPhone(phone))
            {
                cout << "Invalid Phone Number!\n";
                cout << "Please enter exactly 10 digits.\n";
            }

        } while (!validPhone(phone));


        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        // ----------------------------------
        // COMPLAINT DESCRIPTION
        // ----------------------------------

        cout << "Enter Complaint : ";
        getline(cin, problem);


        // New complaint starts as Pending
        status = "Pending";


        cout << "\nComplaint Registered Successfully!\n";
        cout << "Complaint ID : " << id << endl;
        cout << "Status       : " << status << endl;
    }


    // ======================================
    // DISPLAY COMPLAINT
    // ======================================

    void display()
    {
        cout << "\n----------------------------------------\n";
        cout << "Complaint ID : " << id << endl;
        cout << "Name         : " << name << endl;
        cout << "Phone        : " << phone << endl;
        cout << "Complaint    : " << problem << endl;
        cout << "Status       : " << status << endl;
        cout << "----------------------------------------\n";
    }


    // ======================================
    // SEARCH COMPLAINT
    // ======================================

    bool search(int searchId)
    {
        return id == searchId;
    }


    // ======================================
    // UPDATE COMPLAINT STATUS
    // ======================================

    void updateStatus()
    {
        int choice;

        cout << "\nComplaint ID : " << id << endl;
        cout << "Current Status : " << status << endl;

        cout << "\n1. Pending";
        cout << "\n2. Resolved";
        cout << "\nEnter your choice : ";

        cin >> choice;


        if (choice == 1)
        {
            status = "Pending";

            cout << "Status updated to Pending.\n";
        }
        else if (choice == 2)
        {
            status = "Resolved";

            cout << "Status updated to Resolved.\n";
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }


    // ======================================
    // CHECK COMPLAINT STATUS
    // ======================================

    void checkStatus()
    {
        cout << "\n========== COMPLAINT STATUS ==========\n";

        cout << "Complaint ID : " << id << endl;
        cout << "Status       : " << status << endl;
    }


    // ======================================
    // GET STATUS
    // ======================================

    string getStatus()
    {
        return status;
    }
};


// ==========================================
// PRINCIPAL DASHBOARD
// ==========================================

void principalDashboard(Complaint c[], int count)
{
    int choice;


    do
    {
        cout << "\n\n========================================\n";
        cout << "        PRINCIPAL DASHBOARD\n";
        cout << "========================================\n";

        cout << "1. View All Complaints\n";
        cout << "2. Search Complaint\n";
        cout << "3. Update Complaint Status\n";
        cout << "4. Analyse Complaints\n";
        cout << "5. Logout\n";


        cout << "Enter your choice : ";
        cin >> choice;


        switch (choice)
        {

        // ==================================
        // VIEW ALL COMPLAINTS
        // ==================================

        case 1:
        {
            if (count == 0)
            {
                cout << "\nNo complaints available.\n";
            }
            else
            {
                cout << "\n========== ALL COMPLAINTS ==========\n";

                for (int i = 0; i < count; i++)
                {
                    c[i].display();
                }
            }

            break;
        }


        // ==================================
        // SEARCH COMPLAINT
        // ==================================

        case 2:
        {
            int searchId;
            bool found = false;


            cout << "\nEnter Complaint ID to search : ";
            cin >> searchId;


            for (int i = 0; i < count; i++)
            {
                if (c[i].search(searchId))
                {
                    c[i].display();

                    found = true;

                    break;
                }
            }


            if (!found)
            {
                cout << "\nComplaint not found!\n";
            }

            break;
        }


        // ==================================
        // UPDATE COMPLAINT STATUS
        // ==================================

        case 3:
        {
            int updateId;
            bool found = false;


            cout << "\nEnter Complaint ID to update : ";
            cin >> updateId;


            for (int i = 0; i < count; i++)
            {
                if (c[i].search(updateId))
                {
                    c[i].updateStatus();

                    found = true;

                    break;
                }
            }


            if (!found)
            {
                cout << "\nComplaint not found!\n";
            }

            break;
        }


        // ==================================
        // ANALYSE COMPLAINTS
        // ==================================

        case 4:
        {
            int pending = 0;
            int resolved = 0;


            for (int i = 0; i < count; i++)
            {
                if (c[i].getStatus() == "Pending")
                {
                    pending++;
                }
                else if (c[i].getStatus() == "Resolved")
                {
                    resolved++;
                }
            }


            cout << "\n========== COMPLAINT ANALYSIS ==========\n";

            cout << "Total Complaints : " << count << endl;
            cout << "Pending          : " << pending << endl;
            cout << "Resolved         : " << resolved << endl;

            break;
        }


        // ==================================
        // LOGOUT
        // ==================================

        case 5:

            cout << "\nLogged out successfully.\n";

            break;


        default:

            cout << "\nInvalid choice! Please try again.\n";
        }


    } while (choice != 5);
}


// ==========================================
// MAIN FUNCTION
// ==========================================

int main()
{
    // Array to store maximum 50 complaints
    Complaint c[50];


    int count = 0;

    // Complaint IDs start from 101
    int nextId = 101;

    int choice;


    // ======================================
    // MAIN MENU
    // ======================================

    do
    {
        cout << "\n\n========================================\n";
        cout << "       COMPLAINT MANAGEMENT SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Register Complaint\n";
        cout << "2. View Complaints\n";
        cout << "3. Search Complaint\n";
        cout << "4. Check Complaint Status\n";
        cout << "5. Principal Login\n";
        cout << "6. Exit\n";


        cout << "Enter your choice : ";
        cin >> choice;


        switch (choice)
        {

        // ==================================
        // REGISTER COMPLAINT
        // ==================================

        case 1:

            if (count < 50)
            {
                c[count].registerComplaint(nextId);

                count++;

                nextId++;
            }
            else
            {
                cout << "\nComplaint storage is full!\n";
            }

            break;


        // ==================================
        // VIEW COMPLAINTS
        // ==================================

        case 2:

            if (count == 0)
            {
                cout << "\nNo complaints registered yet.\n";
            }
            else
            {
                cout << "\n========== ALL COMPLAINTS ==========\n";


                for (int i = 0; i < count; i++)
                {
                    c[i].display();
                }
            }

            break;


        // ==================================
        // SEARCH COMPLAINT
        // ==================================

        case 3:
        {
            int searchId;
            bool found = false;


            cout << "\nEnter Complaint ID to search : ";
            cin >> searchId;


            for (int i = 0; i < count; i++)
            {
                if (c[i].search(searchId))
                {
                    c[i].display();

                    found = true;

                    break;
                }
            }


            if (!found)
            {
                cout << "\nComplaint not found!\n";
            }

            break;
        }


        // ==================================
        // CHECK COMPLAINT STATUS
        // ==================================

        case 4:
        {
            int statusId;
            bool found = false;


            cout << "\nEnter Complaint ID : ";
            cin >> statusId;


            for (int i = 0; i < count; i++)
            {
                if (c[i].search(statusId))
                {
                    c[i].checkStatus();

                    found = true;

                    break;
                }
            }


            if (!found)
            {
                cout << "\nComplaint not found!\n";
            }

            break;
        }


        // ==================================
        // PRINCIPAL LOGIN
        // ==================================

        case 5:
        {
            string username;
            string password;


            cout << "\n========== PRINCIPAL LOGIN ==========\n";


            cout << "Username : ";
            cin >> username;


            cout << "Password : ";
            cin >> password;


            // Principal credentials
            if (username == "principal" && password == "1234")
            {
                cout << "\nLogin Successful!\n";


                principalDashboard(c, count);
            }
            else
            {
                cout << "\nInvalid Username or Password!\n";
            }


            break;
        }


        // ==================================
        // EXIT
        // ==================================

        case 6:

            cout << "\nThank you for using Complaint Management System!\n";

            break;


        default:

            cout << "\nInvalid choice! Please try again.\n";
        }


    } while (choice != 6);


    // ======================================
    // KEEP TERMINAL OPEN
    // ======================================

    cout << "\nPress Enter to close the program...";


    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cin.get();


    return 0;
}
