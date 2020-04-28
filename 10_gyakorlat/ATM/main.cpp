#include <fstream>
#include <iostream>
#include <vector>


#include "customer.h"

#include "account.h"
#include "bank.h"
#include "card.h"
#include "center.h"


#include "atm.h"

using namespace std;

int main()
{
    Customer* customer = new Customer("Joska");

    Center* c = new Center;
    Bank* otp = new Bank("otp");
    c->registrates(otp);

    Account* account = otp->createAccount("otp1001");
    account->add(10500);

    Card* card = otp->createCard(account, "otpcard1001", "0000");
    customer->takeCard(card);
    card->changePin("0000", "1001");

    ATM* atm = new ATM("valahol", c);
    cout << "Old balance: " << account->getBalance() << endl;
    customer->withdraw(atm);
    cout << "New balance: " << account->getBalance() << endl;

    delete atm;
    delete card;
    delete account;
    delete otp;
    delete c;
    delete customer;

    return 0;
}
