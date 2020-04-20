#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "entry.h"
#include "filesystem.h"
#include <vector>


class FileSystem {
public:
    FileSystem(std::string const& type) : type(type) {}
    ~FileSystem();
    void addEntry(Entry* entry);
    Entry* searchForEntry(std::string const& fname);

private:
    std::vector<Entry*> entries;
    std::string type;
};

#endif
