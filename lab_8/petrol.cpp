#include "petrol.h"

#include "pump.h"
#include "cash.h"

PetrolStation::PetrolStation()
{
    _pumps.resize(6);
    for (unsigned int i = 0; i < _pumps.size(); ++i)
    {
        _pumps[i] = new Pump();
    }
    _cash.resize(2);
    for (unsigned int i = 0; i < _cash.size(); ++i)
    {
        _cash[i] = new Cash(this);
    }
}

PetrolStation::~PetrolStation()
{
    for (Pump *p : _pumps)
        delete p;
    for (Cash *c : _cash)
        delete c;
}
