#include "filesystem.h"

Entry* FileSystem::searchForEntry(std::string const& fname)
{
    /// LinSearch
    for (Entry* e : entries) {
        Entry* found = e->searchFor(fname);
        if (found != nullptr)
            return found;
    }
    return nullptr;
}

void FileSystem::addEntry(Entry* entry)
{
    if (entry != nullptr) {
        entries.push_back(entry);
    }
}
