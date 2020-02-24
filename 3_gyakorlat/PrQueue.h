#ifndef PRQUEUE_H
#define PRQUEUE_H

#include <string>
#include <vector>
#include <iostream>

struct Item
{
    std::string data;
    int priority;
    /** Az alábbi módon adhatunk meg default (alapértelmezett) paramétereket
      * egy függvénynek vagy metódusnak. Amennyiben megadjuk a függvényhívásnál
      * a megfelelő értékeket, akkor azok másolódnak a függvény lokális változóiba,
      * viszont ha nem, akkor azok az egyenlőségjel utáni default értékeket veszik fel.
      * Ez sokkal kényelmesebb, mintha külön konstruktorokat kéne írnunk azokra az
      * esetekre, amikor egyik-másik paraméter hiányzik.
      */
    Item(std::string data = "", int pr = 0) : data(data), priority(pr) {}
    /// A kiíró operátor túlterhelése a múlt órához hasonló módon
    /// történik.
    friend std::ostream &operator<<(std::ostream &os, const Item &e) {
        os << "Nev es pontszam: " << "<" << e.data << ", " << e.priority << ">";
        return os;
    }
    /** A beolvasó operátort is túlterhelhetjük, ugyanúgy, mint a
      * kiíró operátort. Ezzel sokkal olvashatóbb kódot tudunk írni,
      * mivel egy fájlból közvetlenül is beolvashatunk egy Item objektumot.
      */
    friend std::istream &operator>>(std::istream &is, Item &e) {
        is >> e.data >> e.priority; ///felhasznalobarat kiiras!
        return is;
    }
    /// A catch.hpp-vel történő teszteléshez sokkal kényelmesebb,
    /// mint ha egyenként kéne tesztelnünk az adattagok egyenlőségét.
    bool operator==(const Item &e) {
        return (data == e.data && priority == e.priority);
    }
};

class PrQueue
{
    public:
        enum Exception { EMPTY_PRQUEUE };
        PrQueue() : _vec(0) {}
        PrQueue(const std::vector<Item> &vec) {_vec = vec;}
        bool isEmpty() const;
        /// Az item egy összetett struktúra (struct),
        /// így már megszokott módon konstans referenciaként vesszük át.
        void add(const Item &e);
        Item remMax();
        Item getMax() const;
        /** Egy prioritásos sornak alapesetben nem kell biztosítani getLength()
          * metódust (lásd Algoritmusok és adatszerkezetek I.),
          * de a teszteléshez jól fel tudjuk használni, és implementálni
          * is nagyon könnyű.
          */
        int getLength() const {return _vec.size();}
        /** Szintén nem kell egy prioritásos sornak biztosítania azt,
          * hogy le tudjuk kérdezni az i-edik elemét, de a teszteléshez
          * jól fog jönni.
          */
        Item getElement(int index) const {
            return _vec[index];
        }

    private:
        std::vector<Item> _vec;
        int maxIndex() const;
};

#endif
