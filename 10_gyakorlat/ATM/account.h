#pragma once

#include <string>
#include <vector>

#include "card.h"

class Account {
private:
    std::string _accountNo;
    int _balance;

public:
    std::vector<Card*> _cards;

public:
    Account(std::string accountNo)
        : _accountNo(accountNo)
        , _balance(0)
    {
    }
    void addCard(Card* card) { _cards.push_back(card); }

    void add(int a) { _balance += a; }
    int getBalance() const { return _balance; }

    bool cardSearch(const std::string& cardNo) const
    {
        for (Card* card : _cards) {
            if (card->_cardNo == cardNo)
                return true;
        }
        return false;
    }
};
