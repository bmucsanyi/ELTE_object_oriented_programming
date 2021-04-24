#pragma once

#include "atm.h"

class Card;

class Customer
{
private:
    std::string _name;
    std::vector<Card *> _cards;

public:
    enum Errors
    {
        NO_CARD
    };

    Customer(const std::string &name) : _name(name) {}
    std::string getName() const { return _name; }
    void takeCard(Card *card) { _cards.push_back(card); }

    void withdraw(ATM *atm) { atm->process(this); }
    // *(atm).process(this);

    Card *giveCard() const
    {
        if (_cards.size() > 0)  // (!_cards.empty())
            return _cards[0];
        else
            throw NO_CARD;
    }
    std::string givePin() const { return "1001"; }
    int giveAmount() const { return 10000; }
};
