#include "car.h"
#include "petrol.h"
#include "pump.h"
#include "cash.h"

#include <iostream>
#include <sstream>

void Car::refuel(PetrolStation *ps, unsigned int i, int l)
{
    std::ostringstream os1;
    os1 << _name << " starts to fuel\n";
    std::cout << os1.str(); // Red car starts to fuel

    Pump *pump = ps->getPump(i); // get i-th pump
    if (nullptr == pump)
        throw WRONG_PUMP_IDENTITY; // if there's no i-th pump

    pump->fill(l); // refuels with l liter petrol at the i-th pump
    std::ostringstream os2;
    os2 << _name << " is fueling " << l << " liter petrol\n";
    std::cout << os2.str(); // Red car is fueling 20 liter petrol

    int c = chooseCash(ps);
    int n = ps->getCash(c)->pay(i); // payment
    std::ostringstream os3;
    os3 << _name << " has paid: " << n << " Ft" << std::endl;
    std::cout << os3.str();
}

int Car::chooseCash(PetrolStation *ps) const
{
    return rand() % ps->getCashNumber();

    // Generate random numbers from 10..15:
    // rand() % 6; // 0..5
    // rand() % 6 + 10; // 10..15
}
