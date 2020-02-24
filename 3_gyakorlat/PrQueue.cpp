#include "PrQueue.h"

bool PrQueue::isEmpty() const
{
    return _vec.size() == 0;
}

/** Az Item összetett struktúra,
  * így konstans referenciaként vesszük át.
  * (Nem akarjuk módosítani, csak hozzáadni a sorhoz,
  *  ezért jó nekünk, ha konstans.)
  */
void PrQueue::add(const Item& e)
{
    _vec.push_back(e);
}

int PrQueue::maxIndex() const
{
    /** Maximum-kiválasztás tétel.
      * A metódust meghívó függvényeknek / metódusoknak biztosítaniuk
      * kell, hogy csak nemüres PrQueue esetén engedik a metódus
      * meghívását.
      */
    int maxim = _vec[0].priority;
    int ind = 0;
    for(int i = 1; i < int(_vec.size()); ++i) {
        if(_vec[i].priority > maxim) {
            maxim = _vec[i].priority;
            ind = i;
        }
    }
    return ind;
}

Item PrQueue::remMax()
{
    /** Amennyiben üres a prioritásos sorunk,
      * nem tudunk maximális elemet kivenni belőle,
      * így adjunk vissza egy EMPTY_PRQUEUE hibát (kivételt).
      * (Ez valójában egy integer, mivel az enumok 
      *  egyes elemei integerekre képződnek le.)
      */
    if (_vec.size() == 0) throw EMPTY_PRQUEUE;
    int ind = maxIndex(); /// Kiválasztjuk a maximális elem indexét
    Item e = _vec[ind]; /// Kivesszük a maximális elemet
    _vec[ind] = _vec.back(); /// A maximális elemet felülírjuk a vektor utolsó értékével
    _vec.pop_back(); /// Eltávolítjuk a vektor utolsó értékét
    return e;
}

Item PrQueue::getMax() const
{
    /** Lásd remmax, annyi különbséggel,
      * hogy itt nem távolítjuk el a maximális elemet,
      * csak lekérdezzük.
      */
    if (_vec.size() == 0) throw EMPTY_PRQUEUE;
    int ind = maxIndex();
    Item e = _vec[ind];
    return e;
}
