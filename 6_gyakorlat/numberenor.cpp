#include "numberenor.h"

NumberEnor::NumberEnor(const std::string &fn)
{
    f_.open(fn.c_str());
    if (f_.fail())
        throw OPEN_ERROR;
}

void NumberEnor::next()
{
    end_ = (st_ == abnorm);

    if (!end_) {
        /// Alaphelyzetbe állítjuk a jelenlegi elemet.
        nc_.count = 0;
        nc_.number = n_;
        /// Addig olvasunk a fájlból, amíg ugyanazt a számot olvassuk, mint a legutóbbi volt.
        /// (az első iterációnál a ciklusfeltétel mindig triviálisan igaz lesz)
        while (st_ == norm && nc_.number == n_) {
            nc_.count++;
            read();
        }
        /// Mikor itt tartunk, már megfelelő értékek fognak szerepelni az nc_ változónkban.
    }
}

void NumberEnor::read()
{
    if (f_ >> n_) st_ = norm;   /// Ha sikeresen tudtunk olvasni a fájlból...
    else          st_ = abnorm;
}

std::ostream& operator<<(std::ostream &os, const NumberCount &nc)
{
    os << "Number: " << nc.number << "\tCount: " << nc.count;
    return os;
}
