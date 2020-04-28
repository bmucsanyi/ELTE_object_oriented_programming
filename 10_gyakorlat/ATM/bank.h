#pragma once

#include "account.h"
#include "card.h"

#include <string>
#include <vector>

class Bank {
public:
    std::string _code;

private:
    std::vector<Account*> _accounts;

public:
    enum Errors { NONEXISTED_ACCOUNT };

    Bank(std::string code)
        : _code(code)
    {
    }
    Account* createAccount(const std::string& accountNo);
    Card* createCard(Account* pac, const std::string& cardNo, const std::string& pin);

    int getBalance(const std::string& cardNo) const;
    void transaction(const std::string& cardNo, int a);
    bool accountSearch(const std::string& cardNo, Account*& account) const;
};
