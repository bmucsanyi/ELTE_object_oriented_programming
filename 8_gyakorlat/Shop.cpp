#include "Shop.h"

Shop::Shop(const std::string& fname, const std::string& tname)
{
    food = new Department(fname);
    technical = new Department(tname);
}

Shop::~Shop()
{ 
    delete food;
    delete technical;
}
