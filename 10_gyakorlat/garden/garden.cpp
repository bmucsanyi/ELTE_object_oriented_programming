#include "garden.h"

Garden::~Garden()
{
    for (Parcel* p : parcels) {
        delete p;
    }
}

void Garden::setParcel(Plant* p, unsigned int ind, unsigned int date)
{
    if (ind < parcels.size() && parcels[ind] == nullptr) {
        parcels[ind] = new Parcel(p, date);
    }
}
