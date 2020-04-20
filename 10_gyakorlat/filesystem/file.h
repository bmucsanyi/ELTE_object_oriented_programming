#ifndef FILE_H
#define FILE_H

#include "entry.h"
#include <iostream>


class File : public Entry {
public:
    File(const std::string& name, unsigned int size) : Entry(name), size(size) {}
    unsigned int getSize() const override { return size; }
    virtual Entry* searchFor(std::string const& fname) override
    {
        std::cout << "Checking " << name << "...\n";
        if (fname == name)
            return this;
        return nullptr;
    }

protected:
    unsigned int size;
};

#endif
