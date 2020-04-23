#ifndef ENTRY_H
#define ENTRY_H

#include <string>

class Entry {
public:
    Entry(std::string const& name) : name(name) {}
    virtual ~Entry() {}
    std::string getName() const { return name; }
    virtual unsigned int getSize() const = 0;  /* pure virtual */
    virtual Entry* searchFor(std::string const& fname) = 0;

protected:
    std::string name;
};

#endif
