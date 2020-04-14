#ifndef SHOP_H
#define SHOP_H

#include "Department.h"
#include <memory>

class Shop {
public:
    std::shared_ptr<Department> food;
    std::shared_ptr<Department> technical;

    Shop(const std::string& fname, const std::string& tname);
};

#endif
