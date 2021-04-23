#pragma once

class Pump;
class Cash;

#include <vector>

class PetrolStation
{
public:
    PetrolStation();  // construction
    ~PetrolStation(); // destructor

    Cash *getCash(unsigned int i) { return _cash[i]; }
    Pump *getPump(unsigned int i) const { return _pumps[i]; }
    int getUnit() const { return _unit; }
    int getCashNumber() const { return _cash.size(); }

private:
    std::vector<Pump *> _pumps;
    std::vector<Cash *> _cash;
    const int _unit = 400; // price of one liter petrol
};
