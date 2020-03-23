#ifndef FoodEnor_H
#define FoodEnor_H

#include <iostream>
#include <fstream>
#include <sstream>

struct Food {
    std::string name;
    int income;
};

struct Order {
    std::string foodName;
    std::string time;
    int quantity;
    int unitPrice;

    friend std::istream& operator>>(std::istream &is, Order &ord);
};

enum Status {norm, abnorm }; 

class FoodEnor {
public:
    /// Hibakódok felsorolása (Nekünk csak az OPEN_ERROR fontos ebben az esetben)
    enum Error {OPEN_ERROR};
    /// Konstruktor
    FoodEnor(const std::string &str);
    /// Felsoroló megszokott műveletei
    void first();
    void next();
    Food current() { return food; }
    bool end() { return st == abnorm; }

private:
    std::ifstream f;
    Status st;
    Food food;
    Order ord;
};

#endif
