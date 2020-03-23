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
    ~NumberEnor() { f_.close(); }

    void first() { f_ >> n_; next(); }
    void next();
    NumberCount current() const { return nc_; }
    bool end() const { return st_ == abnorm; }

private:
    std::ifstream f_;
    Status st_;
    int n_;
    NumberCount nc_;
};

#endif
