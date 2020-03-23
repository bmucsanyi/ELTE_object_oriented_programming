#include "numberenor.h"

NumberEnor::NumberEnor(const std::string &fn)
{
    f_.open(fn.c_str());
    if (f_.fail())
        throw OPEN_ERROR;
}

void NumberEnor::next()
{
    if (f_.fail()) 
        st_ = abnorm;
    else {
        st_ = norm;
        /// Alaphelyzetbe állítjuk a jelenlegi elemet.
        nc_.count = 0;
        nc_.number = n_;
        /// Addig olvasunk a fájlból, amíg ugyanazt a számot olvassuk, mint a legutóbbi volt.
        /// (az első iterációnál a ciklusfeltétel mindig triviálisan igaz lesz)
        while (!f_.fail() && nc_.number == n_) {
            /** Fontos megjegyezni, hogy az f_.fail() nem azután lesz
              * igaz, miután az utolsó elemet kiolvastuk, hanem miután
              * MEGPRÓBÁLTUK kiolvasni az utolsó utáni elemet, ami nem létezik.
              */
            nc_.count++;
            f_ >> n_;
        }
        /// Mikor itt tartunk, már megfelelő értékek fognak szerepelni az nc_ változónkban.
    }
}

std::ostream& operator<<(std::ostream &os, const NumberCount &nc)
{
    os << "Number: " << nc.number << "\tCount: " << nc.count;
    return os;
}
