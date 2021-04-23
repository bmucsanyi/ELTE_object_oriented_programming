#pragma once

#include <string>

#include <stdlib.h>

class PetrolStation;

enum Errors
{
    WRONG_PUMP_IDENTITY
};

class Car
{
public:
    Car(const std::string &str) : _name(str) {}
    std::string getName() const { return _name; }

    void refuel(PetrolStation *p, unsigned int i, int l);

private:
    std::string _name;

    int chooseCash(PetrolStation *p) const;
};
