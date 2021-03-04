#ifndef OUTFILE_H
#define OUTFILE_H

#include "infile.hpp" // The Cactus struct is needed
#include <fstream>

class Outfile {
public:
    enum Exception { OPEN_ERROR };
    Outfile(const std::string &fname); // Open
    void write(const Cactus &e) { m_f << e << "\n"; }
    void close() { m_f.close(); } /// Close

private:
    std::ofstream m_f;
};

#endif // OUTFILE_H
