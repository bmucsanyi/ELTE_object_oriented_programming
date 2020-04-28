#pragma once

#include "bank.h"
#include <iostream>
#include <vector>

class Center {
private:
    std::vector<Bank*> _banks;

public:
    enum Errors { NO_BANK };

    void registrates(Bank* pbank) { _banks.push_back(pbank); }

    int getBalance(const std::string& bankCode, const std::string& cardNo) const
    {
        return bankSearch(bankCode)->getBalance(cardNo);
    }

    void transaction(const std::string& bankCode, const std::string& cardNo, int a) const
    {
        bankSearch(bankCode)->transaction(cardNo, a);
    }

private:
    Bank* bankSearch(const std::string& bankCode) const
    {
        bool l = false;
        for (Bank* bank : _banks) {
            l = (bank->_code == bankCode);
            if (l)
                return bank;
        }
        throw NO_BANK;
    }
};
