#include <iostream>
#include <cstdlib>
#include "numberenor.h"


using std::cout;
using std::cerr;
using std::endl;

int main()
{
    try {
        NumberEnor t("input.txt");
        /** Most nem feladatunk valamilyen programozási tétel
          * implementálása, csupán fel kell sorolnunk az összes elemet.
          */
        for (t.first(); !t.end(); t.next()) {
            cout << t.current() << endl;
        }
    } catch (NumberEnor::Exception e) {
        cerr << "Opening file failed.\n";
        exit(-1);
    }

    return 0;
}
