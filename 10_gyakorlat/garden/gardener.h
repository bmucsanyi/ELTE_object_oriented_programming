#ifndef GARDENER_H
#define GARDENER_H

#include "garden.h"
#include <iostream>
#include <vector>


class Gardener {
public:
    Gardener(std::string const& name) : name(name) {}
    void plant(Garden& g, char const plantName, unsigned int parcelNum, unsigned int date);
    void list(Garden const& g, unsigned int month);

private:
    std::string name;
};

#endif
