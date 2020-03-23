/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2020. 03. 09.                  *
*   Project name: Restaurant             *
*****************************************/

#include <iostream>
#include <cstdlib>
#include "foodenor.h"

using namespace std;

/** Feladat:
  * Egy étteremben a pincérek által felvett rendeléseket egy szöveges állományban tartják
  * nyilván az ételek neve, azon belül a rendelések időpontja szerint rendezett formában.
  * Feltehetjük, hogy a fájl nem üres. Egy rendelés az asztal sorszámából, a rendelt étel
  * nevéből (sztring), a rendelés időpontjából (sztring), rendelt adagok számából
  * (természetes szám), egy adag árából (természetes szám) áll. Melyik étel hozta az
  * étteremnek a legtöbb bevételt (összesített darab*egységár)?
  */

/// Beolvasás, ügyelve a kiterjesztésre
string beolvas()
{
    cout << "Filename\n>>>";
    string str; cin >> str;
    if (str.size() < 4 || str.substr(str.size()-4, 4) != ".txt") {
        cerr << "Only .txt extensions are allowed!\n";
        exit(1);
    }
    return str;
}

/// Tétel szerinti maximum-kiválasztás, melynek előfeltétele, hogy az input fájl ne legyen üres.
void maxSelect(FoodEnor& t, int &max, Food &elem)
{
    t.first();
    max = t.current().income;
    elem = t.current();
    for (t.next(); !t.end(); t.next()) {
        if (t.current().income > max) {
            max = t.current().income;
            elem = t.current();
        }
    }
}

int main()
{
    string fn = beolvas();
    try {
        FoodEnor t(fn);
        int max;
        Food elem;
        maxSelect(t, max, elem);
        cout << "The food with the highest income this day was " << elem.name << " with " << max << " HUF.\n";
    } catch (FoodEnor::Error e) {
        cerr << "Opening file failed!\n";
        exit(1);
    }
}


