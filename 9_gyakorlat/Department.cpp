#include "Department.h"

Department::Department(const std::string& fileName)
{
    std::ifstream f(fileName.c_str());
    if (f.fail())
        throw OPEN_ERROR;
    std::string productName;
    int price;
    while (f >> productName >> price)
        /// deklaráció: std::shared_ptr<TÍPUS> pointer;
        /// létrehozás: pointer = std::make_shared<TÍPUS>(konstruktor);
        stock.push_back(std::make_shared<Product>(productName, price)); /// stock.push_back(new Product(productName, price));
    f.close();
}

void Department::takeOut(unsigned int ind)
{
    if (ind < stock.size()) {
        /// stock.erase(stock.begin() + ind);
        stock[ind] = stock.back(); /// stock utolsó eleme
        stock.pop_back();
    } else
        throw INVALID_INDEX;
}

std::shared_ptr<Product> Department::getProduct(unsigned int ind) const
{
    if (ind < stock.size())
        return stock[ind];
    throw INVALID_INDEX;
}
