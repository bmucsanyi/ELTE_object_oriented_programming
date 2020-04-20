#include "foodenor.h"

FoodEnor::FoodEnor(const std::string &str)
{
    f_.open(str);
    if (f_.fail()) throw OPEN_ERROR;
}

void FoodEnor::first()
{
    std::string line;
    std::istringstream ss;
    getline(f_, line); ss.str(line); ss >> ord_;
    next();
}

void FoodEnor::next()
{
    if(f_.fail()) { st_ = abnorm; return; }
    st_ = norm;

    std::string line;
    std::istringstream ss;

    food_.name = ord_.foodName;
    food_.income = 0;

    /// Az órai feladathoz teljesen hasonló feldolgozása a fájlnak.
    while (!f_.fail() && ord_.foodName == food_.name) {
        food_.income += (ord_.quantity * ord_.unitPrice);
        getline(f_, line); ss.clear(); ss.str(line); ss >> ord_;
    }
    ss.clear();
    ss.str("");
}

std::istream& operator>>(std::istream& is, Order& ord)
{
    is >> ord.foodName >> ord.time >> ord.quantity >> ord.unitPrice;
    return is;
}
