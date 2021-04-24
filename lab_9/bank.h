#pragma once

#include "account.h"

class Bank
{
public:
    std::string _code;

private:
    std::vector<Account *> _accounts;

public:
    enum Errors
    {
        NONEXISTING_ACCOUNT
    };

    Bank(std::string code) : _code(code) {}
    Account *createAccount(const std::string &accountNo);
    Account *createAccount(const std::string &accountNo, int balance);
    Card *createCard(Account *pac, const std::string &cardNo, const std::string &pin);

    int getBalance(const std::string &cardNo) const;
    void transaction(const std::string &cardNo, int a);

private:
    bool accountSearch(const std::string &cardNo, Account *&account) const;
};
