#ifndef NumberEnor_H
#define NumberEnor_H

#include <cstdlib>
#include <iostream>
#include <fstream>


struct NumberCount {
    int number;
    int count;
    friend std::ostream& operator<<(std::ostream &os, const NumberCount &count);
};

enum Status { norm, abnorm };

class NumberEnor {
public:
    enum Exception {OPEN_ERROR};

    NumberEnor(const std::string &fn);
    ~NumberEnor() { f.close(); }

    void first() { f >> n; next(); }
    void next();
    NumberCount current() const { return nc; }
    bool end() const { return st == abnorm; }

private:
    std::ifstream f;
    Status st;
    int n;
    NumberCount nc;
};

#endif
