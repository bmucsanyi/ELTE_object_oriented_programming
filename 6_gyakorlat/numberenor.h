#ifndef NumberEnor_H
#define NumberEnor_H

#include <cstdlib>
#include <iostream>
#include <fstream>


struct NumberCount {
    int number;
    int count;
    friend std::ostream& operator<<(std::ostream &os, const NumberCount &count);
    /// cout << t.current();
};

enum Status { norm, abnorm };

/// st, e, x: read

class NumberEnor {
public:
    enum Exception { OPEN_ERROR };

    NumberEnor(const std::string &fn);
    ~NumberEnor() { f_.close(); }

    void first() { read(); next(); }
    void next();
    NumberCount current() const { return nc_; }
    bool end() const { return end_; }

private:
    std::ifstream f_;
    Status st_;
    int n_;
    NumberCount nc_;
    bool end_;

    void read();
};

#endif
