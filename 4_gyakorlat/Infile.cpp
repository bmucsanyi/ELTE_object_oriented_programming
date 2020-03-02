#include "Infile.h"

Infile::Infile(const std::string& fname)
{
    f.open(fname.c_str());
    if (f.fail())
        throw OPEN_ERROR;
}

void Infile::next()
{
    std::string line;
    /** A getline függvény alapértelmezett delimitere a '\n' karakter,
      * azaz az első '\n'-ig olvas a file-ból, ami nekünk most pont jó,
      * mert soronként pakoltuk a file-ba az adatokat.
      */
    getline(f, line);
    /// Ha már nem tudtunk olvasni, vagy üres sort olvastunk,
    /// akkor álljunk le.
    if (f.fail() || line == "")
        st = abnorm;
    else {
        st = norm;
        std::istringstream ss(line);
        ss >> e;
        /** Az alábbi két utasítással "kitisztítjuk" a stringstreamet,
          * hogy ne maradjon benne semmi szemét a következő olvasásra.
          * A clear-hez egy rövid ismertető:
          * http://www.cplusplus.com/reference/ios/ios/clear/
          */
        ss.clear();
        ss.str("");
    }
}
