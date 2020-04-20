/**************************
* Author: Bálint Mucsányi *
* Neptun code: JLV5AE     *
* Date: 2019.05.04        *
***************************/

#include "garden.h"
#include "gardener.h"
#include "parcel.h"
#include "plant.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

void destroyPlants()
{
    Potato::destroy();
    Pea::destroy();
    Paprika::destroy();
    Rose::destroy();
    Carnation::destroy();
    Tulip::destroy();
}

void simulation()
{
    /// Feltehetjük, hogy a file formátuma helyes és helyes adatokat tartalmaz.
    cout << "Filename: ";
    string fn;
    cin >> fn;
    ifstream f(fn.c_str());
    if (f.fail()) {
        cout << "Wrong file name!\n";
        exit(1);
    }

    unsigned int gardenSize;
    f >> gardenSize;
    if (f.fail()) {
        cout << "Empty file!\n";
        exit(2);
    }
    Garden garden(gardenSize);

    cout << "Gardener's name: "; /// Nem lényeges a feladat szempontjából.
    string gn;
    cin >> gn;
    Gardener gardener(gn);

    char t;
    unsigned int parcel;
    unsigned int month;
    while (f >> t >> parcel >> month) {
        gardener.plant(garden, t, parcel - 1, month);
    }

    cout << "Which month would you like to list the ripe industrial crops for?\n>>> ";
    unsigned int choice;
    cin >> choice;
    cout << "**************************************" << endl;
    gardener.list(garden, choice);
    cout << "**************************************" << endl;
}

int main()
{
    simulation();
    destroyPlants();
}
