#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip> 
#include <cstdlib> // rand() aur srand() ke liye
#include <ctime>   // time() ke liye

using namespace std;

// Student/User data store karne ke liye structure
struct Student {
    string username;
    string pin;
    double balance = 0.0;
    double loanAmount = 0.0;
    string lastTransaction = "No transaction yet";
};

// Global variables data management ke liye
vector<Student> users;
int totalAccounts = 0;
int idx = -1; // Current logged-in user ka index

// Helper function naye users ko list mein bhejti hai aur random balance deti hai
void addDefaultUser(string name) {
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    replace(name.begin(), name.end(), ' ', '_');
    
    // Random Balance Logic (2000, 3000, 4500, 5000)
    double possibleBalances[] = {2000.0, 3000.0, 4500.0, 5000.0};
    int randomIndex = rand() % 4; // 0, 1, 2, ya 3 select karega
    
    Student s;
    s.username = name;
    s.pin = "1234"; // Default PIN
    s.balance = possibleBalances[randomIndex]; // Random balance assign ho gaya
    
    users.push_back(s);
}

// Saare 68 users ko initialize karne ka function
void initializeAllUsers() {
    string names[] = {
        "Abdullah", "Nouman Ali", "Syed Hussnain Raza Bukhari", "Amber Maqsood", "Shahzad Ali",
        "Abdul Kareem", "Ahsan Ali", "Mehreen Hassan", "Shafique U Rahman", "Saim Ali",
        "Waseem Ali", "Muhammad Atique", "Ishfaque Ali", "Zohaib Ali", "Younis Ali",
        "Abdul Rauf", "Rida Batool", "Sher Muhammad", "Nimra", "Bisharat Ali",
        "Fahad Ali", "Arsalan", "Abdul Razzaque", "Mansoor Ali", "Ashfaque Ahmed",
        "Arsalan_2", "Laiba", "Malaiqa Yameen", "Faizan Mustafa", "Iqra Shafique",
        "Muhammad Muzamil", "Ali Gohar", "Izhar", "Farhan Ali", "Faisal Akbar",
        "Farhan Ali_2", "Fardeen", "Orangzaib", "Mohammad Asif", "Hizbullah",
        "Bakhat Ali", "Hizbullah_2", "Gul Ahmed", "Muhammad Zakria", "Ahmed Mehmood",
        "Wajid Ali", "Ayesha", "Fidak Batool", "Tehmina Bibi", "Muhkum Ul Din",
        "Abdul Shakoor", "Sumera", "Shunaid Ahmed", "Wali Muhammad", "Tazaeen Barkat",
        "Ghous Ali ", "Ahmed Raza", "Ali Raza Memon", "Jatan Kumar", "Farhan Ali Jamali",
        "Abdul Qudoos", "Jameel", "Raj Kumar", "Syed Zakir Hussain Shah", "Mansoor Ali_2",
        "Lakhmir Khan", "Kashif Raza Mari", "Shahbaz Ali"
    };

    int n = sizeof(names) / sizeof(names[0]);
    for (int i = 0; i < n; i++) {
        addDefaultUser(names[i]);
    }
    totalAccounts = users.size();
}

int main() {
    // Seed the random number generator taake har dafa sachi mein alag values aayein
    srand(time(0));
    
    // 68 Users load karna
    initializeAllUsers();
    
    int mainChoice;
    
    while (true) {
        if (idx == -1) {
            cout << "\n====================================" << endl;
            cout << "      WELCOME TO JB BANK SYSTEM  " << endl;
            cout << "====================================" << endl;
            cout << "Total Registered Students: " << totalAccounts << endl;
            cout << "------------------------------------" << endl;
            cout << "1. Student Login" << endl;
            cout << "2. Admin Panel Login" << endl;
            cout << "3. Exit Program" << endl;
            cout << "Enter your choice: ";
            cin >> mainChoice;
            
            if (mainChoice == 1) {
                string user, pass;
                cout << "\n----- STUDENT LOGIN -----\n";
                cout << "Note: Use lowercase & underscore (_) for spaces (e.g., nouman_ali)\n";
                cout << "Enter Username: ";
                cin >> user;
                cout << "Enter PIN: ";
                cin >> pass;
                
                transform(user.begin(), user.end(), user.begin(), ::tolower);
                
                bool loginSuccess = false;
                for (int i = 0; i < totalAccounts; i++) {
                    if (users[i].username == user && users[i].pin == pass) {
                        idx = i;
                        loginSuccess = true;
                        cout << "\nLogin Successful! Welcome, " << users[idx].username << ".\n";
                        system("pause");
                        break;
                    }
                }
                if (!loginSuccess) {
                    cout << "\nInvalid Username or PIN!\n";
                    system("pause");
                }
            }
            else if (mainChoice == 2) {
                string adminUser, adminPass;
                cout << "\n===== ADMIN LOGIN =====\n";
                cout << "Username: ";
                cin >> adminUser;
                cout << "Password: ";
                cin >> adminPass;

                if (adminUser == "jameel" && adminPass == "12345") {
                    
                    // LOGIN PAR SARE 68 STUDENTS KI TABLE DISPLAY KARNA
                    system("cls");
                    cout << "\n=======================================================\n";
                    cout << " " << left << setw(10) << "Roll No" 
                         << setw(30) << "Student Name (Username)" 
                         << "Bank Balance" << "\n";
                    cout << "=======================================================\n";
                    
                    for (int i = 0; i < totalAccounts; i++) {
                        cout << " " << left << setw(10) << (i + 1) 
                             << setw(30) << users[i].username 
                             << "Rs. " << users[i].balance << "\n";
                    }
                    cout << "=======================================================\n";
                    cout << "Total Students Loaded: " << totalAccounts << endl;
                    system("pause");

                    int adminOption;
                    do {
                        system("cls");
                        cout << "\n===== ADMIN JAMEEL =====\n";
                        cout << "1. Add Student\n";
                        cout << "2. Search Student\n";
                        cout << "3. Delete Student\n";
                        cout << "4. View All Registered Students Table\n";
                        cout << "5. Exit Admin Panel\n";
                        cout << "Enter Option: ";
                        cin >> adminOption;

                        switch (adminOption) {
                            case 1: {
                                Student newStudent;
                                cout << "Enter New Student Username (no spaces): ";
                                cin >> newStudent.username;
                                transform(newStudent.username.begin(), newStudent.username.end(), newStudent.username.begin(), ::tolower);
                                cout << "Set PIN: ";
                                cin >> newStudent.pin;
                                cout << "Enter Initial Balance: Rs. ";
                                cin >> newStudent.balance;
                                users.push_back(newStudent);
                                totalAccounts++;
                                cout << "Student Account Created Successfully!\n";
                                system("pause");
                                break;
                            }
                            case 2: {
                                string searchUser;
                                cout << "Enter Username to Search: ";
                                cin >> searchUser;
                                transform(searchUser.begin(), searchUser.end(), searchUser.begin(), ::tolower);
                                bool sFound = false;
                                for(int i=0; i<totalAccounts; i++) {
                                    if(users[i].username == searchUser) {
                                        cout << "\nStudent Found!\n";
                                        cout << "Username: " << users[i].username << endl;
                                        cout << "Balance: Rs. " << users[i].balance << endl;
                                        cout << "Loan Amount: Rs. " << users[i].loanAmount << endl;
                                        sFound = true;
                                        break;
                                    }
                                }
                                if(!sFound) cout << "Student Not Found!\n";
                                system("pause");
                                break;
                            }
                            case 3: {
                                string delUser;
                                cout << "Enter Username to Delete: ";
                                cin >> delUser;
                                transform(delUser.begin(), delUser.end(), delUser.begin(), ::tolower);
                                bool dFound = false;
                                for(size_t i=0; i<users.size(); i++) {
                                    if(users[i].username == delUser) {
                                        users.erase(users.begin() + i);
                                        totalAccounts--;
                                        cout << "Account Deleted Successfully!\n";
                                        dFound = true;
                                        break;
                                    }
                                }
                                if(!dFound) cout << "Student Not Found!\n";
                                system("pause");
                                break;
                            }
                            case 4: {
                                system("cls");
                                cout << "\n=======================================================\n";
                                cout << " " << left << setw(10) << "Roll No" 
                                     << setw(30) << "Student Name" 
                                     << "Bank Balance" << "\n";
                                cout << "=======================================================\n";
                                for(int i=0; i<totalAccounts; i++) {
                                    cout << " " << left << setw(10) << (i + 1) 
                                         << setw(30) << users[i].username 
                                         << "Rs. " << users[i].balance << "\n";
                                }
                                cout << "=======================================================\n";
                                system("pause");
                                break;
                            }
                            case 5:
                                cout << "Exiting Admin Panel...\n";
                                break;
                            default:
                                cout << "Invalid Admin Option!\n";
                                system("pause");
                        }
                    } while (adminOption != 5);
                } else {
                    cout << "Wrong Admin Credentials!\n";
                    system("pause");
                }
            }
            else if (mainChoice == 3) {
                cout << "\nThank you for using our system. Goodbye!\n";
                break;
            }
            else {
                cout << "\nInvalid Selection!\n";
                system("pause");
            }
        } 
        else {
            system("cls");
            
            int userChoice;
            cout << "\n====================================" << endl;
            cout << "          STUDENT DASHBOARD         " << endl;
            cout << "====================================" << endl;
            cout << "Current User: " << users[idx].username << " | Balance: Rs. " << users[idx].balance << endl;
            cout << "------------------------------------" << endl;
            cout << "2. Deposit Money" << endl;
            cout << "3. Withdraw Money" << endl;
            cout << "5. Change PIN" << endl;
            cout << "7. Student To Student Transfer" << endl;
            cout << "8. Loan System" << endl;
            cout << "9. Mobile Load" << endl;
            cout << "10. Utility Bill Payment" << endl;
            cout << "13. JazzCash Transfer" << endl;
            cout << "14. EasyPaisa Transfer" << endl;
            cout << "15. UPaisa Transfer" << endl;
            cout << "16. Forgot PIN" << endl;
            cout << "17. Logout" << endl;
            cout << "====================================" << endl;
            cout << "Enter Option Number: ";
            cin >> userChoice;

            switch (userChoice) {
                case 2: {
                    double amount;
                    cout << "Enter Deposit Amount: ";
                    cin >> amount;

                    if (amount > 0) {
                        users[idx].balance += amount;
                        users[idx].lastTransaction = "Deposited Rs. " + to_string(amount);
                        cout << "Deposit Successful!\n";
                        cout << "New Balance: Rs." << users[idx].balance << endl;
                    } else {
                        cout << "Invalid Amount!\n";
                    }
                    system("pause");
                    break;
                }

                case 3: {
                    double amount;
                    cout << "Enter Withdraw Amount: ";
                    cin >> amount;

                    if (amount <= 0) {
                        cout << "Invalid Amount!\n";
                    } else if (amount > users[idx].balance) {
                        cout << "Insufficient Balance!\n";
                    } else {
                        users[idx].balance -= amount;
                        users[idx].lastTransaction = "Withdraw Rs. " + to_string(amount);
                        cout << "Withdrawal Successful!\n";
                        cout << "Remaining Balance: Rs." << users[idx].balance << endl;
                    }
                    system("pause");
                    break;
                }

                case 5: {
                    string oldPin, newPin;
                    cout << "Enter Old PIN: ";
                    cin >> oldPin;

                    if (oldPin == users[idx].pin) {
                        cout << "Enter New PIN: ";
                        cin >> newPin;
                        users[idx].pin = newPin;
                        cout << "PIN Changed Successfully!\n";
                    } else {
                        cout << "Wrong Old PIN!\n";
                    }
                    system("pause");
                    break;
                }

                case 7: {
                    string receiver;
                    double amount;
                    bool found = false;

                    cout << "Receiver Username: ";
                    cin >> receiver;
                    cout << "Amount: ";
                    cin >> amount;
                    transform(receiver.begin(), receiver.end(), receiver.begin(), ::tolower);

                    for (int i = 0; i < totalAccounts; i++) {
                        if (users[i].username == receiver) {
                            found = true;
                            if (amount > 0 && amount <= users[idx].balance) {
                                users[idx].balance -= amount;
                                users[i].balance += amount;
                                users[idx].lastTransaction = "Transferred Rs. " + to_string(amount) + " to " + receiver;
                                users[i].lastTransaction = "Received Rs. " + to_string(amount) + " from " + users[idx].username;
                                cout << "Transfer Successful!\n";
                            } else {
                                cout << "Insufficient Balance or Invalid Amount!\n";
                            }
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Receiver Not Found!\n";
                    }
                    system("pause");
                    break;
                }

                case 8: {
                    double loan;
                    cout << "Enter Loan Amount: ";
                    cin >> loan;

                    if (loan > 0) {
                        users[idx].loanAmount += loan;
                        users[idx].balance += loan;
                        users[idx].lastTransaction = "Loan Approved Rs. " + to_string(loan);
                        cout << "Loan Added Successfully!\n";
                    } else {
                        cout << "Invalid Loan Amount!\n";
                    }
                    system("pause");
                    break;
                }

                case 9: {
                    string number;
                    double amount;

                    cout << "Mobile Number: ";
                    cin >> number;
                    cout << "Load Amount: ";
                    cin >> amount;

                    if (amount > 0 && amount <= users[idx].balance) {
                        users[idx].balance -= amount;
                        users[idx].lastTransaction = "Mobile Load Rs. " + to_string(amount);
                        cout << "Load Successful!\n";
                    } else {
                        cout << "Insufficient Balance or Invalid Amount!\n";
                    }
                    system("pause");
                    break;
                }

                case 10: {
                    double bill;
                    cout << "Enter Bill Amount: ";
                    cin >> bill;

                    if (bill > 0 && bill <= users[idx].balance) {
                        users[idx].balance -= bill;
                        users[idx].lastTransaction = "Bill Payment Rs. " + to_string(bill);
                        cout << "Bill Paid Successfully!\n";
                    } else {
                        cout << "Insufficient Balance or Invalid Amount!\n";
                    }
                    system("pause");
                    break;
                }

                case 13: {
                    string jcNumber;
                    double amount;
                    cout << "Enter JazzCash Account Number: ";
                    cin >> jcNumber;
                    cout << "Enter Amount: ";
                    cin >> amount;

                    if (amount > 0 && amount <= users[idx].balance) {
                        users[idx].balance -= amount;
                        users[idx].lastTransaction = "JazzCash Transfer Rs. " + to_string(amount);
                        cout << "Rs. " << amount << " Transferred to JazzCash Number " << jcNumber << " Successfully!\n";
                    } else {
                        cout << "Insufficient Balance or Invalid Amount!\n";
                    }
                    system("pause");
                    break;
                }

                case 14: {
                    string epNumber;
                    double amount;
                    cout << "Enter EasyPaisa Account Number: ";
                    cin >> epNumber;
                    cout << "Enter Amount: ";
                    cin >> amount;

                    if (amount > 0 && amount <= users[idx].balance) {
                        users[idx].balance -= amount;
                        users[idx].lastTransaction = "EasyPaisa Transfer Rs. " + to_string(amount);
                        cout << "Rs. " << amount << " Transferred to EasyPaisa Number " << epNumber << " Successfully!\n";
                    } else {
                        cout << "Insufficient Balance or Invalid Amount!\n";
                    }
                    system("pause");
                    break;
                }

                case 15: {
                    string upNumber;
                    double amount;
                    cout << "Enter UPaisa Account Number: ";
                    cin >> upNumber;
                    cout << "Enter Amount: ";
                    cin >> amount;

                    if (amount > 0 && amount <= users[idx].balance) {
                        users[idx].balance -= amount;
                        users[idx].lastTransaction = "UPaisa Transfer Rs. " + to_string(amount);
                        cout << "Rs. " << amount << " Transferred to UPaisa Number " << upNumber << " Successfully!\n";
                    } else {
                        cout << "Insufficient Balance or Invalid Amount!\n";
                    }
                    system("pause");
                    break;
                }

                case 16: {
                    string confirmUser;
                    cout << "To reset PIN, confirm your Username: ";
                    cin >> confirmUser;
                    transform(confirmUser.begin(), confirmUser.end(), confirmUser.begin(), ::tolower);

                    if (confirmUser == users[idx].username) {
                        string newPin;
                        cout << "Identity Verified! Enter New PIN: ";
                        cin >> newPin;
                        users[idx].pin = newPin;
                        cout << "PIN Reset Successfully!\n";
                    } else {
                        cout << "Verification Failed! Cannot Reset PIN.\n";
                    }
                    system("pause");
                    break;
                }

                case 17: {
                    cout << "Logging out from user " << users[idx].username << "...\n";
                    idx = -1;
                    cout << "Logged Out Successfully!\n";
                    system("pause");
                    break;
                }

                default:
                    cout << "Invalid Option Selected!\n";
                    system("pause");
            }
        }
    }
    return 0;
}
