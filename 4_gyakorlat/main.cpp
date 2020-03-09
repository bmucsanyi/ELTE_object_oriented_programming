/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2020. 02. 20.                  *
*   Project name: Cactuses               *
*****************************************/

#include <iostream>
#include <cstdlib>
#include "Infile.h"
#include "Outfile.h"

using namespace std;

/** Feladat:
  *     Adott egy input fájl, amiben soronként kaktuszok adatai
  *     találhatóak.
  *     Írjunk meg egy felsorolót, amely beolvassa az adatokat
  *     és a megszokott műveletekkel rendelkezésünkre is
  *     bocsátja azt.
  *     Implementáljunk objektumorientáltan egy kimeneti fájlkezelő
  *     osztályt is, és ennek segítségével gyűjtsük ki az input
  *     fájlból először a Mexikói kaktuszokat, utána egy másikba
  *     a piros kaktuszokat, majd egy harmadikba a Mexikói ÉS piros
  *     kaktuszokat.
  */

int main()
{
    try {
        Infile t("input.txt");
        Outfile o("output.txt");
        Outfile o2("output2.txt");
        Outfile o3("output3.txt");
        // A táblás struktogramhoz hasonlóan: 
        /** t.first();
          * while(!t.end()) {
          *      cout << t.current() << endl;
          *      t.next();
          * }
          */
        // A for-ciklussal megoldott változat:
        for (t.first(); !t.end(); t.next()){
            if (t.current().home == "Mexiko")
                o.write(t.current());
            if (t.current().color == "piros")
                o2.write(t.current());
            if (t.current().home == "Mexiko" && t.current().color == "piros")
                o3.write(t.current());
        }
        o.close();
        o2.close();
        o3.close();
    } catch(Infile::Exception error) {
        cout << "Infile class, open error.\n";
        exit(1);
    } catch(Outfile::Exception error) {
        cout << "Outfile class, open error.\n";
        exit(2);
    }
    return 0;
}
