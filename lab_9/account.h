#pragma once

#include "card.h"

class Account
{
private:
    std::string _accountNo;
    int _balance;
    std::vector<Card *> _cards;

public:
    Account(const std::string &accountNo) : _accountNo(accountNo), _balance(0) {}
    Account(const std::string &accountNo, int balance) : _accountNo(accountNo), _balance(balance) {}
    void addCard(Card *card) { _cards.push_back(card); }

    void add(int amount) { _balance += amount; }
    int getBalance() const { return _balance; }

    bool has(const std::string &cardNo) const
    {
        for (Card *card : _cards)
        {
            if (card->_cardNo == cardNo)
                return true;
        }
        return false;
    }
};
