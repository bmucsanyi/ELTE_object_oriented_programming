#include "directory.h"
#include "file.h"
#include "filesystem.h"
#include <iostream>

using namespace std;

void createSampleSystem(FileSystem* sys);
void menu(FileSystem* sys);

int main()
{
    FileSystem* sys = new FileSystem("FAT32");
    createSampleSystem(sys);
    menu(sys);
    delete sys;
}

void createSampleSystem(FileSystem* sys)
{
    File* f1 = new File("f1.txt", 1);
    File* f2 = new File("f2.txt", 1);
    Directory* d1 = new Directory("dir1");
    Directory* d2 = new Directory("dir2");

    d1->addEntry(f1);
    d1->addEntry(d2);
    sys->addEntry(d1);
    sys->addEntry(f2);
}

void menu(FileSystem* sys)
{
    /// Feladat: Felhasználó beadja a nevet, system megkeresi, visszatér a pointerével.
    /// Pointer alapján ki kell írni a méretét.
    Entry* ent = sys->searchForEntry("dir13");
    if (ent != nullptr) {
        cout << ent->getSize() << endl;
        return;
    }
    cout << "Entry not found. :(\n";
}
