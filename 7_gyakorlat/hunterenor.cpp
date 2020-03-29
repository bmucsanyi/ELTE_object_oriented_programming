#include "hunterenor.h"

HunterEnor::HunterEnor(const std::string &fileName)
{
    f_.open(fileName.c_str());
    if (f_.fail())
        throw OPEN_ERROR;
}

std::istream& operator>>(std::istream& is, Hunt &h)
{
    /** A beolvasó operátor az input fájl feldolgozására szolgál.
      * Először beolvassuk a következő sort egy string-be a
      * getline() segítségével. Ezután be tudjuk olvasni közvetlenül
      * a vadász nevét és a dátumot.
      * A következő lépésben indítunk egy ciklust, ami feldolgozza
      * a sorban levő állatneveket és súlyokat,
      * és ezekből egy állatot konsturál.
      */
    std::string line;
    getline(is, line);
    std::istringstream ss(line);
    ss >> h.hunterName >> h.date;
    h.animals.clear(); /// Nagyon fontos.

    Animal a;
    while (ss >> a.name >> a.weight) {
        h.animals.push_back(a);
    }
    return is;
}

bool Hunt::bear() const
{
    /// Lineáris keresés programozási tétel.
    for (Animal a : animals) {
        if (a.name == "bear") return true;
    }
    return false;
}

void HunterEnor::next()
{
    end_ = (st_ == abnorm);

    if (!end_) {
        elem_.name = v_.hunterName;
        elem_.bear = v_.bear();

        /// Lineáris keresés programozási tétel, viszont most mindenképp végigmegyünk.
        while (st_ == norm && v_.hunterName == elem_.name){
            if (!elem_.bear) elem_.bear = v_.bear();
            read();
        }
    }
}

void HunterEnor::read()
{
    if (f_ >> v_) st_ = norm;   /// Ha sikeresen tudtunk olvasni a fájlból...
    else          st_ = abnorm;
}
