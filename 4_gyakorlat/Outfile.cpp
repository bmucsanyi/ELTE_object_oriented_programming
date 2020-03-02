#include "Outfile.h"

Outfile::Outfile(const std::string &fname)
{
    f.open(fname.c_str());
    if (f.fail())
        throw OPEN_ERROR;
}
