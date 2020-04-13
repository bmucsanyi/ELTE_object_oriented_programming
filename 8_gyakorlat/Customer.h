#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Shop.h"
#include <fstream>

class Customer {
public:
    enum Exception { OPEN_ERROR,
        NULLPTR_ERROR };
    Customer(const std::string& name, const std::string& fileName);
    void purchase(Shop& shop);
    void putInCart(Product* product);
    friend std::ostream& operator<<(std::ostream& os, const Customer& c);

private:
    std::string name;
    std::vector<std::string> list;
    std::vector<Product*> basket;

    bool linSearch(const std::string& prName, Department* d, unsigned int& ind) const;
    bool minSearch(const std::string& prName, Department* d, unsigned int& ind) const;
};

#endif
