#include "outfile.hpp"

Outfile::Outfile(const std::string &fname)
{
    m_f.open(fname.c_str());
    if (m_f.fail())
        throw OPEN_ERROR;
}
