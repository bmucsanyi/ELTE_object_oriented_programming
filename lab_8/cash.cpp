#include "cash.h"

#include "petrol.h"
#include "pump.h"

int Cash::pay(unsigned int i)
{
    int liter = _petrol->getPump(i)->getQuantity(); // read the i-th pump's display
    _petrol->getPump(i)->resetQuantity();           // zero out the i-th pump's counter
    return liter * _petrol->getUnit();              // full price
}
