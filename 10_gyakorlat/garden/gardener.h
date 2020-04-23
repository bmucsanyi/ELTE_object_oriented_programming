#ifndef GARDENER_H
#define GARDENER_H

#include "garden.h"
#include <iostream>


class Gardener {
public:
    Gardener(std::string const& name, Garden& garden) : name(name), garden(garden) {}
    void plant(char const plantName, unsigned int parcelNum, unsigned int date);
    void list(unsigned int month);

private:
    std::string name;
    Garden garden;
};

#endif
