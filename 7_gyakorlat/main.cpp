/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2020. 03. 29.                  *
*   Project name: Hunt                   *
*****************************************/

#include <iostream>
#include <cstdlib>
#include "hunterenor.h"

using namespace std;

/** Feladat:
  * Egy szekvenciális input fájlban vadászok adott napi vadászatain elejtett zsákmányait
  * (fajtanév és súly párok formájában) vadászok szerint rendezetten tároljuk. Igaz-e,
  * hogy minden vadász valamelyik vadászatán lőtt medvét?
  */

int main()
{
    try {
        HunterEnor t("input2.txt");

        /// Optimista lineáris keresés programozási tétel.
        bool l = true;
        for (t.first(); !t.end(); t.next()) {
            if (!t.current().bear) { l = false; break; }
        }
        if (l) cout << "Every hunter has shot bear.\n";
        else cout << "Not every hunter has shot bear.\n";
    } catch (HunterEnor::Exception e) {
        cerr << "File open error!\n";
        return 1;
    }
}
