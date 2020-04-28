#pragma once

#include <string>
#include <vector>

#include "atm.h"

class Card;

class Customer {
private:
    std::string _name;
    std::vector<Card*> _cards;

public:
    enum Errors { NO_CARD };

    Customer(const std::string& name)
        : _name(name)
        , _cards(0)
    {
    }
    void takeCard(Card* card) { _cards.push_back(card); }

    void withdraw(ATM* atm) { atm->process(this); }

    Card* giveCard() const
    {
        if (_cards.size() > 0)
            return _cards[0];
        else
            throw NO_CARD;
    }
    std::string givePin() const { return "1001"; }
    int giveAmount() const { return 2300; }
};
