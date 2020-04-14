#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
    enum Exception { INVALID_PRICE };
    Product(std::string n, int p)
        : name(n)
        , price(p)
    {
        if (price <= 0)
            throw INVALID_PRICE;
    }
    std::string getName() const { return name; }
    int getPrice() const { return price; }

private:
    std::string name;
    int price;
};

#endif
