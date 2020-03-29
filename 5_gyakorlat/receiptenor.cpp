#include "receiptenor.h"

std::istream& operator>>(std::istream& is, Receipt& r)
{
    r.fullPrice = 0;
    is >> r.name;

    std::string productName;
    unsigned int price;
    while (is >> productName >> price) {
        r.productNames.push_back(productName);
        r.prices.push_back(price);
        r.fullPrice += price; /// Lényegében egy összegzés programozási tétel
    }
    return is;
}

ReceiptEnor::ReceiptEnor(const std::string& fname)
{
    f_.open(fname.c_str());
    if (f_.fail())
        throw OPEN_ERROR;
}

void ReceiptEnor::next()
{
    if (!end_) {
        std::string line;
        /** A getline függvény alapértelmezett delimitere a '\n' karakter,
          * azaz az első '\n'-ig olvas a file-ból, ami nekünk most pont jó,
          * mert soronként pakoltuk a file-ba az adatokat.
          */
        getline(f_, line);
        /// Ha már nem tudtunk olvasni, vagy üres sort olvastunk,
        /// akkor álljunk le.
        if (f_.fail() || line == "")
            st_ = abnorm;
        else {
            st_ = norm;
            std::istringstream ss(line);
            ss >> e_;
            ss.clear();
            ss.str("");
        }
    }
    
    end_ = (st_ == abnorm);
}

void ReceiptEnor::read()
{
    if (f_ >> e_) st_ = norm;   /// Ha sikeresen tudtunk olvasni a fájlból...
    else          st_ = abnorm;
}
