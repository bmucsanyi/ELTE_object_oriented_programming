#include "foodenor.h"

FoodEnor::FoodEnor(const std::string &str)
{
    f.open(str);
    if (f.fail()) throw OPEN_ERROR;
}

void FoodEnor::first()
{
    std::string line;
    std::istringstream ss;
    getline(f, line); ss.str(line); ss >> ord;
    next();
}

void FoodEnor::next()
{
    if(f.fail()) { st = abnorm; return; }
    st = norm;

    std::string line;
    std::istringstream ss;

    food.name = ord.foodName;
    food.income = 0;

    /// Az órai feladathoz teljesen hasonló feldolgozása a fájlnak.
    while (!f.fail() && ord.foodName == food.name) {
        food.income += (ord.quantity * ord.unitPrice);
        getline(f, line); ss.clear(); ss.str(line); ss >> ord;
    }
    ss.clear();
    ss.str("");
}

std::istream& operator>>(std::istream& is, Order& ord)
{
    is >> ord.foodName >> ord.time >> ord.quantity >> ord.unitPrice;
    return is;
}
