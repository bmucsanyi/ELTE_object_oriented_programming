#include "outfile.h"

Outfile::Outfile(const std::string &fname)
{
    f_.open(fname.c_str());
    if (f_.fail())
        throw OPEN_ERROR;
}
