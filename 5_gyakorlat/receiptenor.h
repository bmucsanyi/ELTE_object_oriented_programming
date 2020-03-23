#ifndef RECEIPTENOR_H
#define RECEIPTENOR_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

/** Figyeljük meg, hogy az éppen megadott feladat megoldásához
  * nem lenne szükséges eltárolnunk sem a termékek nevét,
  * sem külön-külön az árukat. Azonban az objektumorientált
  * megvalósítást gyakoroljuk, és egy "Számla" objektumnak
  * vannak terméknevei, sőt, azok árait külön-külön is le
  * tudjuk olvasni egy számláról. Azaz a megfelelő modellezéshez
  * mégis szükség van ezen adattagokra.
  */

struct Receipt {
    std::string name;
    std::vector<std::string> productNames;
    std::vector<unsigned int> prices;
    unsigned int fullPrice;

    friend std::istream& operator>>(std::istream& is, Receipt& r);
};

enum Status { norm, abnorm };

class ReceiptEnor {
public:
    enum Exception { OPEN_ERROR };
    ReceiptEnor(const std::string& fname);         /// Filestream megnyitása
    ~ReceiptEnor() { f_.close(); }                  /// Filestream bezárása
    void first() { next(); }                       /// Felsoroló first művelete (csak olvas)
    void next();                                   /// Felsoroló next művelete (szintén csak olvas)
    Receipt current() const { return e_; }          /// Felsoroló current művelete
    bool end() const { return st_ == abnorm; }      /// Felsoroló end művelete

private:
    /// Nagyon hasonló a táblás gyakorlaton használt jelölésekhez.
    Status st_;
    Receipt e_;
    std::ifstream f_;
};

#endif // ReceiptEnor_H
