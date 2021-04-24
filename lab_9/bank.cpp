#include "bank.h"

Account *Bank::createAccount(const std::string &accountNo)
{
    Account *acc = new Account(accountNo);
    _accounts.push_back(acc);
    return acc;
}

Account *Bank::createAccount(const std::string &accountNo, int balance)
{
    Account *acc = new Account(accountNo, balance);
    _accounts.push_back(acc);
    return acc;
}

Card *Bank::createCard(Account *acc, const std::string &cardNo, const std::string &pin)
{
    if (acc == nullptr)
        throw NONEXISTING_ACCOUNT;
    Card *card = new Card(_code, cardNo, pin);
    acc->addCard(card);
    return card;
}

int Bank::getBalance(const std::string &cardNo) const
{
    Account *account = nullptr;
    if (!accountSearch(cardNo, account))
        throw NONEXISTING_ACCOUNT;
    return account->getBalance();
}

void Bank::transaction(const std::string &cardNo, int a)
{
    Account *account = nullptr;
    if (!accountSearch(cardNo, account))
        throw NONEXISTING_ACCOUNT;
    account->add(a);
}

bool Bank::accountSearch(const std::string &cardNo, Account *&account) const
{
    for (Account *acc : _accounts)
    {
        if (acc->has(cardNo))
        {
            account = acc;
            return true;
        }
    }
    return false;
}
