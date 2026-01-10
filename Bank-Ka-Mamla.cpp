#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Bank {
    int accNo;
    char name[25];
    char fatherName[25];
    char aadhar[25];
    char phone[15];
    char email[30];
    float balance;
    float amount;

    fstream file, tempFile;

public:
    int searchAcc;

    void createAccount();
    void deposit();
    void withdraw();
    void checkInfo();
};

int main() {
    Bank obj;
    char choice;

    while (1) {
        system("cls");
        cout << "\n\t========== BINAYAK'S BANK ==========\n";
        cout << "\t1. Create New Account\n";
        cout << "\t2. Login to Existing Account\n";
        cout << "\t0. Exit\n";
        cout << "\t===================================\n";
        cout << "\tEnter choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            obj.createAccount();
            break;

        case '2':
            cout << "\nEnter Account Number: ";
            cin >> obj.searchAcc;

            while (1) {
                system("cls");
                cout << "\n\t------ ACCOUNT MENU ------\n";
                cout << "\t1. Deposit Amount\n";
                cout << "\t2. Withdraw Amount\n";
                cout << "\t3. Check Account Info\n";
                cout << "\t0. Logout\n";
                cout << "\t--------------------------\n";
                cout << "\tEnter choice: ";
                cin >> choice;

                switch (choice) {
                case '1': obj.deposit(); break;
                case '2': obj.withdraw(); break;
                case '3': obj.checkInfo(); break;
                case '0': goto mainMenu;
                default: cout << "Invalid choice!\n";
                }
                system("pause");
            }

        case '0':
            exit(0);

        default:
            cout << "Invalid choice!\n";
            system("pause");
        }
    }

mainMenu:
    return 0;
}

// ---------- CREATE ACCOUNT ----------
void Bank::createAccount() {
    system("cls");
    srand(time(0));
    accNo = rand() % 900000 + 100000;

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

    file.open("bank.txt", ios::out | ios::app);
    file << accNo << " " << name << " " << fatherName << " "
         << aadhar << " " << phone << " "
         << email << " " << balance << endl;
    file.close();

    cout << "\nAccount Created Successfully!\n";
    cout << "Your Account Number is: " << accNo << endl;
    system("pause");
}

// ---------- DEPOSIT ----------
void Bank::deposit() {
    cout << "\nEnter amount to deposit: ";
    cin >> amount;

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
            cout << "Phone No  : " << phone << endl;
            cout << "Email     : " << email << endl;
            cout << "Balance   : " << balance << endl;
            cout << "-----------------------------\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Account not found!\n";

    file.close();
}
