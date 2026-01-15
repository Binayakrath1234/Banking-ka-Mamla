#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string> 
using namespace std;

class Bank {
    string accNo;
    char name[25];
    char fatherName[25];
    char aadhar[25];
    char phone[15];
    char email[30];
    float balance;
    float amount;

    fstream file, tempFile;

public:
    string searchAcc;

    void createAccount();
    void deposit();
    void withdraw();
    void checkInfo();
};

void wait() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

int main() {
    Bank obj;
    string choice;

    while (true) {
        system("cls");
        cout << "\n\t========== BINAYAK'S BANK ==========\n";
        cout << "\t1. Create New Account\n";
        cout << "\t2. Login to Existing Account\n";
        cout << "\t0. Exit\n";
        cout << "\t===================================\n";
        cout << "\tEnter choice: ";
        getline(cin, choice);

        if (choice == "1") {
            obj.createAccount();
        }
        else if (choice == "2") {
            cout << "\nEnter Account Number: ";
            getline(cin, obj.searchAcc);

            while (true) {
                system("cls");
                cout << "\n\t------ ACCOUNT MENU ------\n";
                cout << "\t1. Deposit Amount\n";
                cout << "\t2. Withdraw Amount\n";
                cout << "\t3. Check Account Info\n";
                cout << "\t0. Logout\n";
                cout << "\t--------------------------\n";
                cout << "\tEnter choice: ";
                getline(cin, choice);

                if (choice == "1") obj.deposit();
                else if (choice == "2") obj.withdraw();
                else if (choice == "3") obj.checkInfo();
                else if (choice == "0") break;
                else cout << "Invalid choice!\n";

                wait();
            }
        }
        else if (choice == "0") {
            exit(0);
        }
        else {
            cout << "Invalid choice!\n";
            wait();
        }
    }
}

// ---------- CREATE ACCOUNT ----------
void Bank::createAccount() {
    system("cls");
    srand(time(0));

    accNo = "";
    for (int i = 0; i < 11; i++)
        accNo += char('0' + rand() % 10);

    cout << "\n------ CREATE NEW ACCOUNT ------\n";
    cout << "Name           : ";
    cin >> name;
    cout << "Father Name    : ";
    cin >> fatherName;
    cout << "Aadhar Number  : ";
    cin >> aadhar;
    cout << "Phone Number  : ";
    cin >> phone;
    cout << "Email ID      : ";
    cin >> email;
    cout << "Initial Amount: ";
    cin >> balance;

    cin.ignore(); // clear buffer

    file.open("bank.txt", ios::out | ios::app);
    file << accNo << " " << name << " " << fatherName << " "
         << aadhar << " " << phone << " "
         << email << " " << balance << endl;
    file.close();

    cout << "\nAccount Created Successfully!\n";
    cout << "Your 11-digit Account Number is: " << accNo << endl;
    wait();
}

// ---------- DEPOSIT ----------
void Bank::deposit() {
    cout << "\nEnter amount to deposit: ";
    cin >> amount;
    cin.ignore();

    file.open("bank.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    while (file >> accNo >> name >> fatherName >> aadhar >> phone >> email >> balance) {
        if (accNo == searchAcc) {
            balance += amount;
            cout << "Updated Balance: " << balance << endl;
        }
        tempFile << accNo << " " << name << " " << fatherName << " "
                 << aadhar << " " << phone << " "
                 << email << " " << balance << endl;
    }

    file.close();
    tempFile.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");
}

// ---------- WITHDRAW ----------
void Bank::withdraw() {
    cout << "\nEnter amount to withdraw: ";
    cin >> amount;
    cin.ignore();

    file.open("bank.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    while (file >> accNo >> name >> fatherName >> aadhar >> phone >> email >> balance) {
        if (accNo == searchAcc) {
            if (balance >= amount) {
                balance -= amount;
                cout << "Updated Balance: " << balance << endl;
            } else {
                cout << "Insufficient Balance!\n";
            }
        }
        tempFile << accNo << " " << name << " " << fatherName << " "
                 << aadhar << " " << phone << " "
                 << email << " " << balance << endl;
    }

    file.close();
    tempFile.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");
}

// ---------- CHECK INFO ----------
void Bank::checkInfo() {
    file.open("bank.txt", ios::in);
    bool found = false;

    while (file >> accNo >> name >> fatherName >> aadhar >> phone >> email >> balance) {
        if (accNo == searchAcc) {
            cout << "\n------ ACCOUNT DETAILS ------\n";
            cout << "Account No : " << accNo << endl;
            cout << "Name       : " << name << endl;
            cout << "Father     : " << fatherName << endl;
            cout << "Aadhar No  : " << aadhar << endl;
            cout << "Phone No   : " << phone << endl;
            cout << "Email      : " << email << endl;
            cout << "Balance    : " << balance << endl;
            cout << "-----------------------------\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Account not found!\n";

    file.close();
}
