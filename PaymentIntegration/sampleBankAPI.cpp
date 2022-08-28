// Banking System
// Author Ibsa Abraham
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
using namespace std;

int query();
struct Account
{
    string fname, lname,fullName, accountType;
    int accountNumber;
    float balance;
    float interestRate;
    bool activeUser;
    Account *nextAccount;
};

Account *first, *last,  *User[100];

// functions 
void createAccount();
void userList(Account *[], int);
void customerList();
int withDraw();
void Deposit();
int accountNumberCheck();
void checkBalance();
void deleteAccount(Account *[]);
void transferBalance(Account *[]);

// global variables
int counter = 0;   // represents both active user and inactive user;
int inactive_user_counter = 0;
string accType[2] = {"WI ", "WOI"};
int main()
{

    first = NULL;
    last = NULL;
    bool isTrue =  true;
    while(isTrue) {
        int returnValue = query();
        switch (returnValue)
        {
        case 1:
            createAccount();
            break;
        case 2:
             Deposit();
             break;
        case 3:
             withDraw();
             break;
        case 4:
             checkBalance();
             break;
        case 5:
             deleteAccount(User);
             break;
        case 6:
             transferBalance(User);
             break;
        case 7:
             customerList();
             break;
            
        case 8:
             isTrue = false;
             break;
        default:
            break;
        }
    }
    
}

int query() {
    int choice;
        cout << "Temporary Bank \n"
         << "[1] To create Account \n"
         << "[2] Deposit Money \n"
         << "[3] Withdraw Money\n"
         << "[4] Check Balance \n"
         << "[5] Delete Account \n"
         << "[6] Transfer  Money \n"
         << "[7] LIst of all Users \n"
         << "[8] Exit \n";
    cin >> choice;
    return choice;
}

void createAccount() {
    system("cls");
    User[counter] = new Account;
    cout << "Account Registration \n";
    cout << "First Name: "; cin >> User[counter]->fname;
    cout << "Last Name: "; cin >> User[counter]->lname;
    User[counter]->fullName = User[counter]->fname + " " + User[counter]->lname;

    cout << "Initial Deposit \n";
    cin >> User[counter]->balance;
    while(User[counter]->balance < 25) {cout << "Incorrect\n"; cin >> User[counter]->balance;}

        cout << "Account Type: With Interest(Y/N)\n";
    char type; cin >> type;
    if(type=='Y') {
        User[counter]->accountType = accType[1];

    } else if (type=='N') {
        User[counter]->accountType = accType[0];
    } else {
        cout << "Please enter the correct output \n";
    }
        User[counter]->accountNumber = 1000 + counter;
        User[counter]->activeUser = true;
    // next Account in the list;
    if(first==NULL) {
        first = User[counter];
        last = User[counter];
        
    } else {
        last->nextAccount = User[counter];
        last = User[counter];
    }
    cout << "Account created succesfuly \n";
    counter++;
}

// individual account information;
void userList(Account *userInfo[100], int i) {
    if(userInfo[i]->activeUser) {
        cout << userInfo[i]->fullName << right << setw(10)
             << userInfo[i]->accountNumber << right << setw(15)
             << userInfo[i]->accountType << right << setw(19)
             << userInfo[i]->balance 
             << endl;
    }
}

// all customers list;
void customerList() 
{
    system("cls");
    cout << "Full Name" << right << setw(20) << "Account Number" 
         << right << setw(15) << "Account Type " 
         << right << setw(15) << "Balance\n";
    // to traverse through each customer;
    for (int i = 0; i < (counter); i++)
        userList(User, i);
}

int accountNumberCheck() {
    int accountNum;
    cout << "Account Number: ";
    cin >> accountNum;
    for(int i = 0; i < counter; i++)
        if(accountNum==User[i]->accountNumber)   // does account number exist;
             if(User[i]->activeUser)             // is the account active;
                   return i;
}

int withDraw() {
    system("cls");
    int fromAccountIndex = accountNumberCheck();
    cout << "Many to withdraw \n";
    int withdrawMoney;
    cin >> withdrawMoney;

            User[fromAccountIndex]->balance -=withdrawMoney;
            cout << "Transaction completed \n";

    return 0;
}

void Deposit() {
    system("cls");
    int accountToIndex = accountNumberCheck();
    cout << "Enter deposit Money: \n";
    int depositMoney;
    cin >> depositMoney;

    User[accountToIndex]->balance +=depositMoney;
    cout << "Transaction completed \n";
}

void checkBalance() {
    system("cls");
    int accountBalanceCheck = accountNumberCheck();
    cout <<"Balance: " <<  User[accountBalanceCheck]->balance << endl;
}

void deleteAccount(Account *UserAccount[]) {
    system("cls");
    int del_index = accountNumberCheck();
    if(del_index > 0) {
        UserAccount[del_index-0]->nextAccount = UserAccount[del_index]->nextAccount;
        delete UserAccount[del_index];
    } else if(del_index ==0) {
        first = UserAccount[del_index];
        first->nextAccount = UserAccount[del_index]->nextAccount;
        delete first;
    }
    cout << "Account Deleted Successfuly \n";
    UserAccount[del_index]->activeUser = false;
    inactive_user_counter++;
}

void transferBalance(Account *userAccount[]) {
    system("cls");
    int accountFrom, accountTo;
    cout << "Sender "; accountFrom = accountNumberCheck();
    cout << "Reciever "; accountTo = accountNumberCheck();
    cout << "Amount of money to be transferred \n";

    float transferredMoney; cin >> transferredMoney;

    if(userAccount[accountFrom]->activeUser && userAccount[accountTo]->activeUser) {
        if(userAccount[accountFrom]->balance > transferredMoney) {
            userAccount[accountTo]->balance += transferredMoney;
            userAccount[accountFrom]->balance -= transferredMoney;
        } else cout << "Insufficient balance \n";
    } else {
        cout << "Account was deactivated: " << endl;
    }
    cout << "Transaction completed \n";
}