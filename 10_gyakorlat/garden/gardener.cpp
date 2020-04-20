#include "gardener.h"

void Gardener::plant(Garden& g, const char plantName, unsigned int parcelNum, unsigned int date)
{
    switch (plantName) {
    case 'o':
        g.setParcel(Potato::instance(), parcelNum, date);
        break;
    case 'e':
        g.setParcel(Pea::instance(), parcelNum, date);
        break;
    case 'a':
        g.setParcel(Paprika::instance(), parcelNum, date);
        break;
    case 'r':
        g.setParcel(Rose::instance(), parcelNum, date);
        break;
    case 'c':
        g.setParcel(Carnation::instance(), parcelNum, date);
        break;
    case 't':
        g.setParcel(Tulip::instance(), parcelNum, date);
        break;
    }
}

void Gardener::list(Garden const& g, unsigned int month)
{
    for (unsigned int i = 0; i < g.getSize(); ++i) {
        if (g.getParcel(i)->getPlant()->isIndustrialCrop && (g.getParcel(i)->getPlant()->getRipeningTime() + g.getParcel(i)->getPlantDate()) % 12 == month) { //(g.getParcel(i)->getPlant()->getRipeningTime() + g.getParcel(i)->getPlantDate())%12 <= month) {
            std::cout << "Industrial crop in parcel " << i + 1 << " is ripe." << std::endl;
        }
    }
}
