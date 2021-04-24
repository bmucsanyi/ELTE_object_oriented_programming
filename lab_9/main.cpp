#include <fstream>
#include <sstream>
#include <iostream>

#include "customer.h"
#include "center.h"

using namespace std;

void createBanks(const string &fileName, Center *&center, vector<Customer> &customers);
int findCustomer(const string &name, const vector<Customer> &customers);

int main()
{
    Center *c = new Center();
    vector<Customer> customers;
    createBanks("input/banks.txt", c, customers);
    ATM *atm = new ATM("somewhere", c);
    for (Customer cust : customers)
    {
        try
        {
            Card *card = cust.giveCard();
            cout << cust.getName() << "'s old balance: " << c->getBalance(card->_bankCode, card->_cardNo) << endl;
            cust.withdraw(atm);
            cout << "\tSuccess!\n";
            cout << cust.getName() << "'s new balance: " << c->getBalance(card->_bankCode, card->_cardNo) << endl;
        }
        catch (ATM::Errors ex)
        {
            if (ex == ATM::FEW_MONEY)
            {
                cout << "\tFew money!\n";
            }
            else if (ex == ATM::WRONG_PIN_CODE)
            {
                cout << "\tWrong pin code!\n";
            }
        }
    }

    delete c;
    delete atm;

    return 0;
}

int findCustomer(const string &name, const vector<Customer> &customers)
{
    for (unsigned int i = 0; i < customers.size(); ++i)
    {
        if (customers[i].getName() == name)
            return i;
    }
    return -1;
}

void createBanks(const string &fileName, Center *&center, vector<Customer> &customers)
{
    ifstream f(fileName.c_str()); /// in banks.txt there are the names of the banks
    string bankName;
    while (f >> bankName)
    {
        Bank *bank = new Bank(bankName);
        center->registrates(bank);
        ifstream bankStream(("input/" + bankName + ".txt").c_str()); /// in bankname.txt there are the account numbers with customer names, balances, and card numbers
        string line;
        getline(bankStream, line, '\n');
        while (!bankStream.fail()) /// reading accounts
        {
            stringstream ss(line);
            string accountNo, owner;
            int balance;
            ss >> owner >> accountNo >> balance;
            int customerIndex = findCustomer(owner, customers); ///check if there is such customer in the vector
            if (customerIndex == -1)                            /// if not, push_back
            {
                customerIndex = customers.size();
                customers.push_back(Customer(owner));
            }
            Account *acc = bank->createAccount(accountNo, balance); /// create the account
            string cn, p;
            while (ss >> cn >> p) /// read the corresponding cards
            {
                Card *card = new Card(bankName, cn, p);
                acc->addCard(card);                      /// assign card to account
                customers[customerIndex].takeCard(card); ///assign card to customer
            }
            getline(bankStream, line, '\n');
        }
        bankStream.close();
    }
    f.close();
}
