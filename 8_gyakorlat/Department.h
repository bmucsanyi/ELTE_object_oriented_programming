#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Product.h"
#include <fstream>
#include <memory>
#include <vector>


class Department {
public:
    enum Exception { OPEN_ERROR,
        INVALID_INDEX };
    /// Mivel összetett adatstruktúra, nem érték szerint adunk át, mivel nem
    /// szeretjük ezeket másolgatni.
    Department(const std::string& fileName);
    void takeOut(unsigned int ind);
    std::shared_ptr<Product> getProduct(unsigned int ind) const;
    unsigned int stockPiece() const { return stock.size(); }

private:
    std::vector<std::shared_ptr<Product>> stock;
};

#endif
