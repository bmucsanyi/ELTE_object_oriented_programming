#ifndef HUNTERENOR_H
#define HUNTERENOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct Animal {
    std::string name;
    int weight;
};

struct Hunt {
    std::string hunterName;
    std::string date;
    std::vector<Animal> animals;
    friend std::istream &operator>>(std::istream &is, Hunt &h);
    bool bear() const;
};

struct Hunter {
    std::string name;
    bool bear;
};

enum Status { norm, abnorm };

class HunterEnor {
public:
    enum Exception {OPEN_ERROR};
    HunterEnor(const std::string &fileName);
    ~HunterEnor() { f_.close(); }
    void first() { read(); next(); }
    void next();
    Hunter current() const { return elem_; }
    bool end() const { return end_; }
private:
    std::ifstream f_;
    Status st_;
    Hunt v_;
    Hunter elem_;
    bool end_;

    void read();
};

#endif
