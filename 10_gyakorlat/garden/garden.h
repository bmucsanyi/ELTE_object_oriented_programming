#ifndef GARDEN_H
#define GARDEN_H

#include "parcel.h"
#include "plant.h"
#include <iostream>
#include <vector>


class Garden {
public:
    ///Constructor && Destructor
    Garden(unsigned int size) : parcels(size, nullptr) {}
    ~Garden();
    ///Getter & Add
    Parcel* getParcel(unsigned int i) const
    {
        if (i < parcels.size())
            return parcels[i];
        else
            return nullptr;
    }
    unsigned int getSize() const { return parcels.size(); }
    void setParcel(Plant* p, unsigned int ind, unsigned int date);

private:
    std::vector<Parcel*> parcels;
};

#endif
