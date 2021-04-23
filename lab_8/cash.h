#pragma once

class PetrolStation;

class Cash
{
public:
    Cash(PetrolStation *p) : _petrol(p) {}
    int pay(unsigned int i);

private:
    PetrolStation *_petrol;
};
