#pragma once

#include "bank.h"

class Center
{
private:
    std::vector<Bank *> _banks;

public:
    enum Errors
    {
        NO_BANK
    };

    void registrates(Bank *bank) { _banks.push_back(bank); }

    int getBalance(const std::string &bankCode, const std::string &cardNo) const
    {
        // Bank* bank = bankSearch(bankCode);
        // return bank->getBalance(cardNo);
        return bankSearch(bankCode)->getBalance(cardNo);
    }

    void transaction(const std::string &bankCode, const std::string &cardNo, int a) const
    {
        bankSearch(bankCode)->transaction(cardNo, a);
    }

private:
    Bank *bankSearch(const std::string &bankCode) const
    {
        bool l = false;
        for (Bank *bank : _banks)
        {
            l = (bank->_code == bankCode);
            if (l)
                return bank;
        }
        throw NO_BANK;
    }
};
