#include "gardener.h"

void Gardener::plant(char const plantName, unsigned int parcelNum, unsigned int date)
{
    switch (plantName) {
    case 'o':
        garden.setParcel(Potato::instance(), parcelNum, date);
        break;
    case 'e':
        garden.setParcel(Pea::instance(), parcelNum, date);
        break;
    case 'a':
        garden.setParcel(Paprika::instance(), parcelNum, date);
        break;
    case 'r':
        garden.setParcel(Rose::instance(), parcelNum, date);
        break;
    case 'c':
        garden.setParcel(Carnation::instance(), parcelNum, date);
        break;
    case 't':
        garden.setParcel(Tulip::instance(), parcelNum, date);
        break;
    }
}

void Gardener::list(unsigned int month)
{
    for (unsigned int i = 0; i < garden.getSize(); ++i) {
        if (garden.getParcel(i)->getPlant()->isIndustrialCrop &&
           (garden.getParcel(i)->getPlant()->getRipeningTime() +
            garden.getParcel(i)->getPlantDate()) % 12 == month) {
            std::cout << "Industrial crop in parcel " << i + 1 << " is ripe." << std::endl;
        }
    }
}
