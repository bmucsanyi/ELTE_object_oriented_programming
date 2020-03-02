#ifndef INFILE_H
#define INFILE_H

#include <iostream>
#include <fstream>
#include <sstream>

struct Kaktusz
{
    std::string name;
    std::string home;
    std::string size;
    std::string color;

    friend std::ostream& operator<<(std::ostream& os, const Kaktusz& k) {
        os << "Name: " << k.name << "\tCountry: " << k.home << "\tSize: " << k.size << "\tColor: " << k.color;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Kaktusz& k) {
        is >> k.name >> k.home >> k.size >> k.color;
        return is;
    }
};

enum Status {norm, abnorm};

class Infile
{
    public:
        enum Exception {OPEN_ERROR};
        Infile(const std::string& fname);         /// Filestream megnyitása
        ~Infile() { f.close(); }                  /// Filestream bezárása
        void first() { next(); }                  /// Felsoroló first művelete (csak olvas)
        void next();                              /// Felsoroló next művelete (szintén csak olvas)
        Kaktusz current() const { return e; }     /// Felsoroló current művelete
        bool end() const { return st == abnorm; } /// Felsoroló end művelete

    private:
        /// Nagyon hasonló a táblás gyakorlaton használt jelölésekhez.
        Status st;
        Kaktusz e;
        std::ifstream f;
};

#endif // INFILE_H
