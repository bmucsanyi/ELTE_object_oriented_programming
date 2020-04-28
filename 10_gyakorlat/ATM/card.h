#pragma once

#include <string>
#include <vector>

class Card {
public:
    std::string _bankCode;
    std::string _cardNo;

private:
    std::string _pinCode;

public:
    Card(const std::string& bank, const std::string& cardNo)
        : _bankCode(bank)
        , _cardNo(cardNo)
        , _pinCode("0000")
    {
    }

    void changePin(const std::string& oldpin, const std::string& pin)
    {
        if (oldpin == _pinCode)
            _pinCode = pin;
    }

    bool pinCheck(const std::string& pin) const { return pin == _pinCode; }
};
