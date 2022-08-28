#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
struct account
{
    string name;
    int account;
    float balance;
    int securityCode;
    bool is_prepaid;
};
account *user[100];

// random number generator;
int random2[10] = {};
int random1[10] = {};

void random_generator(int random_assign[10])
{
    for (int i = 0; i < 10; i++)
    {
        int random_number = 1000 + rand() % (9001);
        random_assign[i] = random_number;
    }
};

// creates account for  10 user
void bankInformation()
{
    for (int i = 0; i < 10; i++)
    {
        user[i] = new account;
        user[i]->name = " ";
        user[i]->account = 1000 + i;
        user[i]->balance = random1[i];
        user[i]->securityCode = random2[i];
    }

    /* divide the first 5 accounts to non-prepaid and 
    the last 5 accounts to prepaid */

    for (int i = 0; i < 5; i++)
        user[i]->is_prepaid = false;
    for (int i = 5; i < 10; i++)
        user[i]->is_prepaid = true;
}

// creating prepaid account for the user
int prepd_ct = 10;
void create_prepaidAccount()
{
	system("cls");
    user[prepd_ct] = new account;
    cout << "Enter your full name: ";
    string fname, lname; 
    cin >> fname >> lname;
    user[prepd_ct]->name  = fname + " " + lname;
    cout << "Enter Initial Balance: ";
    cin >> user[prepd_ct]->balance;
    cout << "create a new password (must be number): ";
    cin >> user[prepd_ct]->securityCode;

    user[prepd_ct]->account = 1000 + prepd_ct;
    user[prepd_ct]->is_prepaid = true;

    cout << "Account Created Succesfully, Thanks for choosing us\n";
    cout << "Your prepaid account Number is " << user[prepd_ct]->account << endl;
    prepd_ct++;
}

// deposit to prepaid card
void deposit_prepaid()
{
		system("cls");
    int cardNumber;
    unsigned int deposit_money;
    cout << "Enter prepaid card Number: ";
    cin >> cardNumber;

    // check whether prepaid account exists
    int acc_index;
    bool acc_exist = false;
    for (int i = 0; i < (prepd_ct); i++)
        if (user[i]->is_prepaid && cardNumber == user[i]->account)
        {
            acc_index = i;
            acc_exist = true;
        }

    if (acc_exist)
    {
        cout << "Enter money to be deposited: ";
        cin >> deposit_money;
        user[acc_index]->balance += deposit_money;
        cout << "Your prepaid balance now is " << user[acc_index]->balance << endl;
    }
    else
        cout << "Prepaid card account does not exist \n";
}

// to see changes to customer bank account;
void show_bank_information()
{
	cout << "Account Balance prepaid/not security code\n";
    for (int i = 0; i < (prepd_ct); i++)
    {
        cout << user[i]->account << "  "
			<< user[i]->balance << "  " 
			<< user[i]->is_prepaid << "\t"
            << " " << user[i]->securityCode << endl;
    }
}


/* checks whether the customer have enough balance  and provided 
correct security code and account Number to reserve a seat
It also checks type of bank account whether it's prepaid or not */
bool accountCheck(float payement, int account, int securityCode, bool isPrepaid, bool txn_status)
{
    bool success_txn = false;
    bool is_found = false;
    int acc_index;

    // checks wether the account number and password exists;
    for (int i = 0; i < (prepd_ct); i++)
    {
        if ((user[i]->account == account) &&
            (user[i]->securityCode == securityCode) &&
            (isPrepaid == user[i]->is_prepaid))
        {
            acc_index = i;
            is_found = true;
        }
    }

    // if the account is found
    if (is_found)
    {
        if (txn_status) // if the status is reservation
        {
            if (user[acc_index]->balance > payement)
            {
                user[acc_index]->balance -= payement;
                success_txn = true;
            }
            else
            {
                cout << "No Sufficient balance \n";
                success_txn = false;
            }
        }
        else // if the status is cancelling reservation
        {
            user[acc_index]->balance += payement;
            success_txn = true;
        }
    }
    else
    {
        cout << "The Account Number or password is not correct \n";
        success_txn = false;
    }
    return success_txn;
}
