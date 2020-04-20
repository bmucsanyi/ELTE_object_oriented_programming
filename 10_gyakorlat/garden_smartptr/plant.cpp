#include "plant.h"
/// Industrial crops
/// Potato
std::shared_ptr<Potato> Potato::inst = nullptr;

std::shared_ptr<Potato> Potato::instance()
{
    if (inst == nullptr) {
        inst = std::make_shared<Potato>();
    }
    return inst;
}

/// Pea
std::shared_ptr<Pea> Pea::inst = nullptr;

std::shared_ptr<Pea> Pea::instance()
{
    if (inst == nullptr) {
        inst = std::make_shared<Pea>();
    }
    return inst;
}

/// Paprika
std::shared_ptr<Paprika> Paprika::inst = nullptr;

std::shared_ptr<Paprika> Paprika::instance()
{
    if (inst == nullptr) {
        inst = std::make_shared<Paprika>();
    }
    return inst;
}

/// Flowers
/// Rose
std::shared_ptr<Rose> Rose::inst = nullptr;

std::shared_ptr<Rose> Rose::instance()
{
    if (inst == nullptr) {
        inst = std::make_shared<Rose>();
    }
    return inst;
}

/// Carnation
std::shared_ptr<Carnation> Carnation::inst = nullptr;

std::shared_ptr<Carnation> Carnation::instance()
{
    if (inst == nullptr) {
        inst = std::make_shared<Carnation>();
    }
    return inst;
}

/// Tulip
std::shared_ptr<Tulip> Tulip::inst = nullptr;

std::shared_ptr<Tulip> Tulip::instance()
{
    if (inst == nullptr) {
        inst = std::make_shared<Tulip>();
    }
    return inst;
}
