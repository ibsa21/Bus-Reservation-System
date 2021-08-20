#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
struct accountNumber
{
    string name;
    int account;
    float balance;
    int securityCode;
    
};

accountNumber user[10];

void bankInformation() {
    for(int i = 0; i < 10; i++) {
            user[i].name = " ";
    user[i].account = 1000 + i;
    user[i].balance = 1000;
    user[i].securityCode = 1000 + rand()%(9001);
    cout << user[i].securityCode << endl;
    }
}

bool accountCheck(float payement, int account, int securityCode ) {
     bool isExist = false;
    for(int i = 0; i < 10; i++)
        if((user[i].account==account && user[i].balance > payement) && (user[i].securityCode==securityCode)){
            isExist = true;
            user[i].balance -=payement;
        }

    return isExist;
}