#include "bank.h"

#include <iostream>

Account* Bank::createAccount(const std::string& accountNo)
{
    Account* acc = new Account(accountNo);
    _accounts.push_back(acc);
    return acc;
}

Card* Bank::createCard(Account* acc, const std::string& cardNo, const std::string& pin)
{
    if (acc == nullptr)
        throw NONEXISTED_ACCOUNT;
    Card* card = new Card(_code, cardNo);
    acc->_cards.push_back(card);
    return card;
}

int Bank::getBalance(const std::string& cardNo) const
{
    Account* account = nullptr;
    if (!accountSearch(cardNo, account))
        throw NONEXISTED_ACCOUNT;
    return account->getBalance();
}

void Bank::transaction(const std::string& cardNo, int a)
{
    Account* account = nullptr;
    if (!accountSearch(cardNo, account))
        throw NONEXISTED_ACCOUNT;
    account->add(a);
}

bool Bank::accountSearch(const std::string& cardNo, Account*& account) const
{
    for (Account* acc : _accounts) {
        account = acc;
        for (Card* card : account->_cards) {
            if (card->_cardNo == cardNo)
                return true;
        }
    }
    return false;
}
