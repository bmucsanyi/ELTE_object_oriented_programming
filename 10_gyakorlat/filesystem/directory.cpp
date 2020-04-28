#include "directory.h"

unsigned int Directory::getSize() const
{
    /// Summation
    unsigned int s = 0;
    for (Entry* e : entries) {
        s += e->getSize();
    }
    return s;
}

Entry* Directory::searchFor(std::string const& fname)
{
    /// LinSearch
    std::cout << "Looking into " << name << "...\n";
    if (fname == name)
        return this;
    for (Entry* e : entries) {
        Entry* found = e->searchFor(fname);
        if (found != nullptr)
            return found;
    }
    return nullptr;
}

void Directory::addEntry(Entry* entry)
{
    if (entry != nullptr) {
        entries.push_back(entry);
    }
}
