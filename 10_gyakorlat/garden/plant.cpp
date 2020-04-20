#include "plant.h"
/// Industrial crops
/// Potato
Potato* Potato::inst = nullptr;

Potato* Potato::instance()
{
    if (inst == nullptr) {
        inst = new Potato();
    }
    return inst;
}

void Potato::destroy()
{
    if (inst != nullptr)
        delete inst;
}

/// Pea
Pea* Pea::inst = nullptr;

Pea* Pea::instance()
{
    if (inst == nullptr) {
        inst = new Pea();
    }
    return inst;
}

void Pea::destroy()
{
    if (inst != nullptr)
        delete inst;
}

/// Paprika
Paprika* Paprika::inst = nullptr;

Paprika* Paprika::instance()
{
    if (inst == nullptr) {
        inst = new Paprika();
    }
    return inst;
}

void Paprika::destroy()
{
    if (inst != nullptr)
        delete inst;
}

/// Flowers
/// Rose
Rose* Rose::inst = nullptr;

Rose* Rose::instance()
{
    if (inst == nullptr) {
        inst = new Rose();
    }
    return inst;
}

void Rose::destroy()
{
    if (inst != nullptr)
        delete inst;
}

/// Carnation
Carnation* Carnation::inst = nullptr;

Carnation* Carnation::instance()
{
    if (inst == nullptr) {
        inst = new Carnation();
    }
    return inst;
}

void Carnation::destroy()
{
    if (inst != nullptr)
        delete inst;
}

/// Tulip
Tulip* Tulip::inst = nullptr;

Tulip* Tulip::instance()
{
    if (inst == nullptr) {
        inst = new Tulip();
    }
    return inst;
}

void Tulip::destroy()
{
    if (inst != nullptr)
        delete inst;
}
