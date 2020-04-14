#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Shop.h"
#include <fstream>
#include <memory>

class Customer {
public:
    enum Exception { OPEN_ERROR,
        NULLPTR_ERROR };
    Customer(const std::string& name, const std::string& fileName);
    void purchase(Shop& shop);
    void putInCart(std::shared_ptr<Product> product);
    friend std::ostream& operator<<(std::ostream& os, const Customer& c);

private:
    std::string name;
    std::vector<std::string> list;
    std::vector<std::shared_ptr<Product>> basket;

    bool linSearch(const std::string& prName, std::shared_ptr<Department> d, unsigned int& ind) const;
    bool minSearch(const std::string& prName, std::shared_ptr<Department> d, unsigned int& ind) const;
};

#endif
