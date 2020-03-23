#include "numberenor.h"

NumberEnor::NumberEnor(const std::string &fn)
{
    f.open(fn.c_str());
    if (f.fail())
        throw OPEN_ERROR;
}

void NumberEnor::next()
{
    if (f.fail()) 
        st = abnorm;
    else {
        st = norm;
        /// Alaphelyzetbe állítjuk a jelenlegi elemet.
        nc.count = 0;
        nc.number = n;
        /// Addig olvasunk a fájlból, amíg ugyanazt a számot olvassuk, mint a legutóbbi volt.
        /// (az első iterációnál a ciklusfeltétel mindig triviálisan igaz lesz)
        while (!f.fail() && nc.number == n) {
            /** Fontos megjegyezni, hogy az f.fail() nem azután lesz
              * igaz, miután az utolsó elemet kiolvastuk, hanem miután
              * MEGPRÓBÁLTUK kiolvasni az utolsó utáni elemet, ami nem létezik.
              */
            nc.count++;
            f >> n;
        }
        /// Mikor itt tartunk, már megfelelő értékek fognak szerepelni az nc változónkban.
    }
}

std::ostream& operator<<(std::ostream &os, const NumberCount &nc)
{
    os << "Number: " << nc.number << "\tCount: " << nc.count;
    return os;
}
