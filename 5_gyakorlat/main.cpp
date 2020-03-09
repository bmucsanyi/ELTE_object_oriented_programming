/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2020. 03. 09.                  *
*   Project name: Receipts               *
*****************************************/

#include <iostream>
#include <cstdlib>
#include "receiptenor.h"

using namespace std;

/** Feladat:
  *     Adott egy számítástechnikai üzlet aznapi forgalma:
  *     számlák sorozata, ahol egy számlán szerepel a vásárló neve,
  *     az általa vásárolt termékek neve és ára.
  *     Mennyi az aznapi bevétel?
  * 
  *     Szorgalmi:
  *     Folytassuk az órai feladatot! Van-e olyan számla, amelyben csupa
  *     legalább 20000 Ft-os termékek szerepelnek?
  *     Az órai feladattól eltérő módon a vásárló neve több tagból is állhat,
  *     enélkül a feladat nem ér pontot.
  *     (Ötlet: Mentsük el az addig olvasott neveket, és addig olvassunk a
  *             név adattagba, amíg az aktuális beolvasott string már nem nagybetűvel
  *             kezdődik. Ekkor már tudjuk, hogy az a terméknév.
  *     )
  */

int main()
{
    try {
        ReceiptEnor enor("input.txt");

        /// Összegzés programozási tétel felsorolókra
        unsigned int sum = 0;
        for (enor.first(); !enor.end(); enor.next()) {
            sum += enor.current().fullPrice;
        }

        cout << "Today's income is " << sum << " Forints." << endl;
    } catch(ReceiptEnor::Exception error) {
        cerr << "File open error.\n";
        exit(1);
    }

    return 0;
}
