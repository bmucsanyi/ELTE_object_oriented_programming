#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "entry.h"
#include <vector>
#include <iostream>

class Directory : public Entry {
public:
    Directory(std::string const& name) : Entry(name) {}
    unsigned int getSize() const override;
    Entry* searchFor(const std::string& fname) override;
    void addEntry(Entry* entry);

protected:
    std::vector<Entry*> entries;
};

#endif
