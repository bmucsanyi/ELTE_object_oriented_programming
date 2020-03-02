#ifndef OUTFILE_H
#define OUTFILE_H

#include "Infile.h" // A Kaktusz struct-ra szükségünk van.
#include <fstream>

class Outfile
{
    public:
        enum Exception { OPEN_ERROR };
        Outfile(const std::string &fname); /// Nyitás
        void write(const Kaktusz &e) { f << e << "\n"; }
        void close() { f.close(); } /// Zárás

    private:
        std::ofstream f;
};

#endif // OUTFILE_H
