#ifndef PARCEL_H
#define PARCEL_H

#include "plant.h"

class Parcel {
public:
    Parcel(Plant* p, unsigned int plantDate) : p(p), plantDate(plantDate) {}
    /// Getter
    Plant* getPlant() const { return p; }
    /// Setter
    void setPlant(Plant* pl) { p = pl; }
    unsigned int getPlantDate() const { return plantDate; }

private:
    Plant* p;
    unsigned int plantDate;
};

#endif
