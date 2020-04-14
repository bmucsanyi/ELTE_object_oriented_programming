#include "Shop.h"

Shop::Shop(const std::string& fname, const std::string& tname)
{
    food = std::make_shared<Department>(fname);
    technical = std::make_shared<Department>(tname);
}
