#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>
using namespace std;

class temp{
    int accNo;
    char name[25];
    char Fname[25];
    char cnic[25];
    char P_no[25];
    char email[25];
    float amount;
    int newAmount;
    fstream file,file1;

public:
    int search;

    void createAccount(void);
    void depositAmount(void);
    void withdrawAmount(void);
    void checkInfo(void);
};

int main(){

    temp obj;
    char choice;

    cout<<"\n\n\n\t\t......:::Binayak's Bank:::......";
    cout<<"\n\t\t:: press 1 to Login  Account :: ";
    cout<<"\n\t\t:: press 2 to Create Account ::";
    cout<<"\n\t\t:: press 0 to Exit           ::";
    cout<<"\n\t\t:: ......................... ::\n\t\t\t\t";
    cin>>choice;
    
    switch(choice){
        case '1':
            cout<<"Enter your account no :: ";
            cin>>obj.search;

            while(1){
                cout<<"\n\n\n\t\t.......:::Binayak's Bank:::.......";
                cout<<"\n\t\t:: press 1 to Deposit  Amount  :: ";
                cout<<"\n\t\t:: press 2 to Withdraw Amount  ::";
                cout<<"\n\t\t:: press 3 to Check    Info    ::";
                cout<<"\n\t\t:: press 0 to Exit     Menu    ::";
                cout<<"\n\t\t:: ........................... ::\n\t\t\t\t";
                cin>>choice;

                switch (choice){
                case '1':
                    obj.depositAmount();
                    break;
                case '2':
                    obj.withdrawAmount();
                    break;
                case '3':
                    obj.checkInfo();
                    break;
                case '0':
                    return 0;
                default:
                    cout<<"Invalid Choice...!";
                }
                system("pause");
                system("cls");
            }
        case '2':
            obj.createAccount();
            break;
        case '0':
            return 0;
        default:
            cout<<"\n Invalid choice...! ";
    }
    return 0;
}

// ---- CREATE ACCOUNT ----
void temp :: createAccount(){

    srand(time(0));
    accNo = rand()*rand()+rand()*rand();

    cout<<"Enter Your name :: ";
    cin>>name;

    cout<<"Enter Your Father name :: ";
    cin>>Fname;

    cout<<"Enter Your cnic :: ";
    cin>>cnic;

    cout<<"Enter Your phone no. :: ";
    cin>>P_no;

    cout<<"Enter Your email :: ";
    cin>>email;

    cout<<"Enter Your amount :: ";
    cin>>amount;

    cout<<endl<<accNo<<" This is your account number...\n";
    cout<<"Please save it\n\n";

    file.open("data.txt",ios::out|ios::app);
    file<<accNo<<"\t"<<name<<"\t"<<Fname<<"\t"<<cnic<<"\t"
        <<P_no<<"\t"<<email<<"\t"<<amount<<endl;
    file.close();
}

// -------- DEPOSIT ------
void temp :: depositAmount(){

    cout<<"Enter amount to deposit :: ";
    cin>>newAmount;

    file.open("data.txt",ios::in);
    file1.open("data1.txt",ios::out|ios::app);

    while(file>>accNo>>name>>Fname>>cnic>>P_no>>email>>amount){
        if(accNo==search){
            cout<<"\nCurrent amount :: "<<amount;
            amount += newAmount;
            cout<<"\nUpdated amount :: "<<amount<<endl;
        }
        file1<<accNo<<"\t"<<name<<"\t"<<Fname<<"\t"<<cnic<<"\t"
             <<P_no<<"\t"<<email<<"\t"<<amount<<endl;
    }

    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt","data.txt");
}

// ------ WITHDRAW ------
void temp :: withdrawAmount(){

    cout<<"Enter amount to withdraw :: ";
    cin>>newAmount;

    file.open("data.txt",ios::in);
    file1.open("data1.txt",ios::out|ios::app);

    while(file>>accNo>>name>>Fname>>cnic>>P_no>>email>>amount){
        if(accNo==search){
            cout<<"\nCurrent amount :: "<<amount;
            amount -= newAmount;
            cout<<"\nUpdated amount :: "<<amount<<endl;
        }
        file1<<accNo<<"\t"<<name<<"\t"<<Fname<<"\t"<<cnic<<"\t"
             <<P_no<<"\t"<<email<<"\t"<<amount<<endl;
    }

    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt","data.txt");
}

// ------ CHECK INFO -------
void temp :: checkInfo(){

    file.open("data.txt",ios::in);
    if(!file){
        cout<<"File opening error!";
        return;
    }

    while(file>>accNo>>name>>Fname>>cnic>>P_no>>email>>amount){
        if(accNo==search){
            cout<<"\n---------------------------\n";
            cout<<"\t::: Account Number ::: "<<accNo<<endl;
            cout<<"\t::: User Name      ::: "<<name<<endl;
            cout<<"\t::: Father Name    ::: "<<Fname<<endl;
            cout<<"\t::: CNIC           ::: "<<cnic<<endl;
            cout<<"\t::: Phone Number   ::: "<<P_no<<endl;
            cout<<"\t::: Email          ::: "<<email<<endl;
            cout<<"\t::: Current Amount ::: "<<amount<<endl;
            cout<<"---------------------------\n\n";
        }
    }
    file.close();
}
