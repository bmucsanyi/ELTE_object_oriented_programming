#ifndef SHOP_H
#define SHOP_H

#include "Department.h"

class Shop {
public:
    Department* food;
    Department* technical;

    Shop(const std::string& fname, const std::string& tname);
    ~Shop();
};

#endif
