#ifndef PARCEL_H
#define PARCEL_H

#include "plant.h"

class Parcel {
public:
    Parcel(std::shared_ptr<Plant> p, unsigned int plantDate) : p(p), plantDate(plantDate) {}
    /// Getter
    std::shared_ptr<Plant> getPlant() const { return p; }
    /// Setter
    void setPlant(std::shared_ptr<Plant> pl) { p = pl; }
    unsigned int getPlantDate() const { return plantDate; }

private:
    std::shared_ptr<Plant> p;
    unsigned int plantDate;
};

#endif
