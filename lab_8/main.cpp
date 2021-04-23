#include <iostream>
#include <sstream>
#include <time.h>

#include "petrol.h"
#include "car.h"

using namespace std;

int main()
{
    srand(time(nullptr));

    PetrolStation p;
    Car *a = new Car("red car");
    a->refuel(&p, 3, 25);

    return 0;
}