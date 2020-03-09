/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2020. 02. 08.                  *
*   Project name: Highest valley         *
*****************************************/

/// Settings -> Editor -> SpellChecker -> Kiszedni a pipákat
/// Settings -> Compiler -> Have g++ follow the C++11 ISO C++ language standard

#include <iostream>
#include <vector>
#include <fstream>
#include "stdlib.h"

/// 1. Beadandó sorszámának kiosztása folyamatban
/// Szorgalmi: Egy tömb leggyakoribb elemének megkeresése maximum-kiválasztásba ágyazott számlálással.
/// (bin és obj mappákat kérlek töröljétek Canvas-be feltöltéskor, melynek létrehozása szintén folyamatban)

/// Az általunk jelenleg használt névtérbe bevezetjük
/// az összes std (standard) névtérben található
/// függvényt, osztályt, konstanst.
using namespace std;

vector<int> setup(string fileName)
{
    /// Létrehozunk egy input file streamet (ifstream),
    /// amely konstruktorának megadjuk a file nevét,
    /// amelyből olvasni akarunk.
    ifstream f(fileName.c_str()); //atoi-nál is szükségünk lesz a c_str()-re

    /// f.fail(): Valamilyen okból nem tudjuk megnyitni a megadott file-t.
    /// Okok lehetnek: Nincs olvasási jogosultságunk a file-ra, vagy nem létezik.
    if (f.fail()) {
        cerr << "Invalid file name.\n"; // #include <iostream>
        exit(1); // #include "stdlib.h"
    }

    int e;

    /// Létrehozunk egy std::vector példányt.
    /// Ezzel egyesek találkozhattak progalapon,
    /// de a legtöbben egyszerű tömböket használtatok.
    /// Az std::vector egy dinamikus tömb, amely átméretezhető
    /// a program futása során.
    /// Ez egy template osztály (érdeklődők nézzenek utána),
    /// így '<>' jelek között adjuk meg a template paramétert,
    /// azaz ebben az esetben azt, hogy milyen típusú elemeket
    /// tartalmaz az std::vector.
    vector<int> vec; // #include <vector>
    while (f >> e) {
        /// A push_back az std::vector egy metódusa,
        /// mellyel az adott std::vector végére
        /// hozzáadhatunk egy elemet.
        vec.push_back(e);
        cout << e << " ";
    }

    cout << endl << endl;
    return vec;
}

/// Ha referencia szerint veszünk át egy paramétert (&),
/// akkor nem másoljuk le az adott értéket, hanem egy álnevet
/// hozunk létre rá, melyen keresztül ugyanúgy elérhető és módosítható is
/// az adott objektum.
/// (Lényegében olyan, mintha egy pointert használnánk, viszont nem kell
///  a dereferálással bajlódnunk.)
/// A másolás elkerülésével gyakran sokkal hatékonyabb, mint a cím szerinti
/// paraméterátadás.
/// Ebben a függvényben azonban nem szeretnénk az input vektor értékeit megváltoztatni,
/// így a const kulcsszóval látjuk el.
bool condMaxSearch(const vector<int>& vec, int& maxDepth, int& ind)
{
    bool l = false;
    for (int i = 1; i < int(vec.size() - 1); i++) {
        if (l && vec[i+1] > vec[i] && vec[i-1] > vec[i]) {
            if (maxDepth < vec[i]) {
                maxDepth = vec[i];
                ind = i;
            }
        }
        else if (!l && vec[i+1] > vec[i] && vec[i-1] > vec[i]) {
            l = true;
            maxDepth = vec[i];
            ind = i;
        }
        /// Teljesen felesleges:
        // else {
        //     continue;
        // }
    }
    /// Ezt ne:
    // if (l) return true;
    // else return false;
    /// Helyette:
    return l;
}

int main()
{
    int maxDepth, ind;
    vector<int> heights = setup("input3.txt");
    if (condMaxSearch(heights, maxDepth, ind)) {
        cout << "Maximum depth: " << maxDepth << " Index: " << ind + 1 << "." << endl;
    }
    else {
        cout << "There are no valleys.\n";
    }
    return 0;
}
