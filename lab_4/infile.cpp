#include "infile.hpp"

Infile::Infile(const std::string &fname)
{
    m_f.open(fname.c_str());
    if (m_f.fail())
        throw OPEN_ERROR;
}

void Infile::next()
{
    std::string line;
    /* The getline function's default delimiter is the newline character
     * ('\n'), thus it reads characters from the file until the first
     * encountered '\n', which is perfect for us in this case, as we
     * put the data in the file line by line.
     */
    getline(m_f, line);
    // If we cannot read from the file, or if we read an empty line,
    // we should stop.
    if (m_f.fail() || line == "")
        m_st = abnorm;
    else {
        m_st = norm;
        std::istringstream ss(line);
        ss >> m_e;
        /* With the two statements below we "clear" the stringstream,
         * so as not to leave any rubbish in it for the upcoming reads.
         * A short introduction to strinstream.clear():
         * http://www.cplusplus.com/reference/ios/ios/clear/
         */
        ss.clear();
        ss.str("");
    }
}
