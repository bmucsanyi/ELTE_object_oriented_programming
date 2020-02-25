/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2020. 02. 24.                  *
*   Project name: PrQueue and testing    *
*****************************************/

#include <iostream>
#include <vector>
#include "PrQueue.h"
#include "menu.h"

/** Ezen a gyakorlaton egy PrQueue-t, azaz egy prioritásos sort
  * fogunk implementálni.
  * Ennek főbb metódusai (műveletei):
  *     isEmpty, add, remMax, max
  * További kiegészítő metódusok, csupán teszteléshez:
  *     operator==, getLength, getElement
  * A belső reprezentációt egy std::vector segítségével oldjuk meg.
  * Ennek dinamikus voltát kihasználjuk (nincs max méret, szükség szerint bővül)
  * a tábláshoz gyakorlathoz képest, tehát
  * m (maximális mérete a prioritásos sornak) nem kell,
  * n (vec.size()) szintén nem kell.
  *
  * Táblán: Item = rec(string, int)
  * Egy Item-nek van egy data és egy priority adattagja.
  * A priority adattag szükséges ahhoz, hogy valamilyen prioritási
  * sorrendet fel tudjunk állítani. A data adattag hordozza az item
  * valódi adatát.
  *
  * METÓDUSOK RÖVID LEÍRÁSA:
  * isEmpty: Megnézi, hogy üres-e a prioritásos sor.
  *  - Belső vektor reprezentáció size()-át kell vizsgálni.
  * add: Hozzáad egy Item-et a prioritásos sorhoz.
  *  - A belső vektor reprezentáció push_back metódusát használjuk.
  * remMax: Kiveszi a maximális elemet a prioritásos sorból.
  *  - Maximum-kiválasztás tételt implementálunk, kimentjük a maximális
  *    elemet, majd helyére a vektor utolsó elemét írjuk,
  *    és töröljük az utolsó elemet (pop_back metódus)
  * max: Visszaadja a maximális elemet a prioritásos sorból.
  *  - Lásd remMax, annyi különbséggel, hogy nem vesszük ki
  *    a maximális elemet a vektorból.
  * 
  * SZORGALMI FELADAT:
  * Implementáljátok a síkbeli vektorok osztályát (típusát).
  * Szükséges műveletek: Összeadás, skaláris szorzat.
  * Feladat: Adottak vektorok egy fájlban. (vektor1.x  vektor1.y vektor2.x vektor2.y ...)
  * Beolvasunk console-ról is egy vektort (cin).
  * A fájlból beolvasott vektorok összege merőleges-e a console-ról beolvasott vektorra?
  * Reminder: Merőlegesek, ha skaláris szorzatuk 0.
  * Írjatok beolvasó és kiíró operátorokat is a vektor osztályotoknak.
  */

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

vector<Item> setup()
{
    int db;
    vector<Item> v;
    cout << "Please provide the number of contestants. (n)\n>>>";
    cin >> db;
    cout << "Please provide the (n) names and (n) results:\n>>>";
    Item tmp;
    for(int i = 0; i < db; ++i) {
        cin >> tmp;
        // cout << tmp << endl; - Ellenőrzés
        v.push_back(tmp);
    }
    return v;
}

int main()
{
  /*
   * vector<Item> vec = setup();
   * PrQueue PrQ(vec);
   * cout << PrQ.getMax();
   *
   * return 0;
   */
  cout << "Priority queue" << endl;

    Menu Test;
    Test.run();

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("isEmpty")
{
    PrQueue PQ;
    CHECK(PQ.isEmpty());

    Item e("data", 1);
    PQ.add(e);
    CHECK(!PQ.isEmpty());

    e = PQ.remMax();
    CHECK(PQ.isEmpty());
}

TEST_CASE("remMax")
{
    Item e("data1", 1);
    Item e2("data2", 2);
    Item e3("data2", 3);
    Item e4("data2", 4);
    Item e5("data2", 5);
    /// Felsoroló szerinti tesztelés
    SECTION("empty prqueue") /// Üres felsoroló
    {
        PrQueue PQ;
        /** Leteszteljük, hogy kivételt vált ki, ha
          * üres prioritásos sorból akarunk maximális
          * elemet eltávolítani.
          */
        CHECK_THROWS(e = PQ.remMax());
    }
    SECTION("prqueue with one element") /// Üres felsoroló
    {
        PrQueue PQ;
        PQ.add(e2);
        e = PQ.remMax();
        /** Vegyük észre, hogy az alábbi sor csak azért működik megfelelően, mert
          * megírtuk az "Item" típusra az egyenlőség operátort.
          * Enélkül fordítási hibát kapnánk, mivel nem tudná a fordító,
          * hogy mi alapján kéne vizsgálni két "Item" objektum egyenlőségét.
          */
        CHECK(e == e2);
    }
    SECTION("prqueue with more elements", "max in the beginning of prqueue")
    {
        PrQueue PQ;
        PQ.add(e5);
        PQ.add(e2);
        PQ.add(e3);
        e = PQ.remMax();
        /// Megvizsgáljuk, hogy valóban a maximális elemet kaptuk-e vissza
        CHECK(e == e5);
        CHECK(PQ.getLength() == 2);
        CHECK(PQ.getElement(0) == e3);
        CHECK(PQ.getElement(1) == e2);
    }
    /** Ide elférnének még olyan tesztesetek, melyben szintén több elemű
      * prioritásos sort vizsgálunk, melynek a maximális eleme a belső vektor
      * utolsó eleme, vagy a közepén van a maximális eleme.
      */
    SECTION("prqueue with more elements",
            "more than one maximal values, which are in the first positions")
    {
        PrQueue PQ;
        PQ.add(e5);
        PQ.add(e5);
        PQ.add(e3);
        e = PQ.remMax();
        CHECK( e==e5); //Sorrend vizsg�lata
        CHECK( PQ.getLength()==2);
        CHECK( PQ.getElement(0)==e3);
        CHECK( PQ.getElement(1)==e5);
    }
    /** További tesztelési lehetőségek: (Elvártak)
      * Több elem, több max, maxok a végén
      * Több elem, mind max
      * Ha használnánk összegzést, ott terhelési tesztet
      * is végrehajtanánk, itt erre nincs szükségünk
      * (Lásd előadás diák!)
      */
}

#endif
