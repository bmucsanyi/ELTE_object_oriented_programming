#include "prqueue.h"

bool PrQueue::isEmpty() const
{
    return vec_.size() == 0;
}

/** Az Item összetett struktúra,
  * így konstans referenciaként vesszük át.
  * (Nem akarjuk módosítani, csak hozzáadni a sorhoz,
  *  ezért jó nekünk, ha konstans.)
  */
void PrQueue::add(const Item& e)
{
    vec_.push_back(e);
}

int PrQueue::maxIndex() const
{
    /** Maximum-kiválasztás tétel.
      * A metódust meghívó függvényeknek / metódusoknak biztosítaniuk
      * kell, hogy csak nemüres PrQueue esetén engedik a metódus
      * meghívását.
      */
    int maxim = vec_[0].priority;
    int ind = 0;
    for(int i = 1; i < int(vec_.size()); ++i) {
        if(vec_[i].priority > maxim) {
            maxim = vec_[i].priority;
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
    if (vec_.size() == 0) throw EMPTY_PRQUEUE;
    int ind = maxIndex(); /// Kiválasztjuk a maximális elem indexét
    Item e = vec_[ind]; /// Kivesszük a maximális elemet
    vec_[ind] = vec_.back(); /// A maximális elemet felülírjuk a vektor utolsó értékével
    vec_.pop_back(); /// Eltávolítjuk a vektor utolsó értékét
    return e;
}

Item PrQueue::getMax() const
{
    /** Lásd remmax, annyi különbséggel,
      * hogy itt nem távolítjuk el a maximális elemet,
      * csak lekérdezzük.
      */
    if (vec_.size() == 0) throw EMPTY_PRQUEUE;
    int ind = maxIndex();
    Item e = vec_[ind];
    return e;
}
