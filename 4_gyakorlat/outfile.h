#ifndef OUTFILE_H
#define OUTFILE_H

#include "infile.h" // A Kaktusz struct-ra szükségünk van.
#include <fstream>

class Outfile {
public:
    enum Exception { OPEN_ERROR };
    Outfile(const std::string &fname); /// Nyitás
    void write(const Kaktusz &e) { f_ << e << "\n"; }
    void close() { f_.close(); } /// Zárás

private:
    std::ofstream f_;
};

#endif // OUTFILE_H
