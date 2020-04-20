#include "garden.h"

void Garden::setParcel(std::shared_ptr<Plant> p, unsigned int ind, unsigned int date)
{
    if (ind < parcels.size() && parcels[ind] == nullptr) {
        parcels[ind] = new Parcel(p, date);
    }
}
