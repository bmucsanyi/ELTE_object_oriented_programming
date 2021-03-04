#ifndef INFILE_H
#define INFILE_H

#include <iostream>
#include <fstream>
#include <sstream>

struct Cactus {
    std::string name;
    std::string home;
    std::string size;
    std::string color;

    friend std::ostream& operator<<(std::ostream& os, const Cactus& k) {
        os << "Name: " << k.name << "\tCountry: " << k.home << "\tSize: " << k.size << "\tColor: " << k.color;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Cactus& k) {
        is >> k.name >> k.home >> k.size >> k.color;
        return is;
    }
};

enum Status { norm, abnorm };

class Infile {
public:
    enum Exception {OPEN_ERROR};
    Infile(const std::string& fname);           // Opening filestream
    ~Infile() { m_f.close(); }                  // Closing filestream
    void first() { next(); }                    // 'First' operation of the enumerator (only reads now)
    void next();                                // 'Next' operation of the enumerator (simply reads, too)
    Cactus current() const { return m_e; }      // 'Current' operation of the enumerator
    bool end() const { return m_st == abnorm; } // 'End' operation of the enumerator
private:
    /// Very similar to the notation used on the practice
    Status m_st;
    Cactus m_e;
    std::ifstream m_f;
};

#endif // INFILE_H
