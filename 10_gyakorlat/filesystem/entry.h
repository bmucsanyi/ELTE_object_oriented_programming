#ifndef ENTRY_H
#define ENTRY_H

#include <string>

class Entry {
public:
    Entry(std::string const& name) : name(name) {}
    virtual ~Entry() {}
    std::string getName() const { return name; }
    virtual unsigned int getSize() const = 0;
    virtual Entry* searchFor(std::string const& fname) { return nullptr; }

protected:
    std::string name;

private:
};

#endif
