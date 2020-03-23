#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/** Figyelem!
  * Az alábbi megoldás jóval kompaktabb, egyszerűbb,
  * mint az órai.
  * Ilyen egyszerű feladat esetén sokszor redundáns
  * lehet felsoroló osztályt létrehozni és azzal dolgozni.
  * Azonban a ZH-n már a megfelelt szinthez is elvárás,
  * hogy osztályokkal dolgozzatok!
  * A 3-as szinthez pl. elég lehet az, hogy a lenti
  * read metódust a file, status és számla objektumokkal
  * együtt egy osztályba csomagoljátok, melynek egy
  * számla lekérdező metódusa van, illetve
  * a már említett read metódus, a logika pedig marad ugyanez.
  * Ennél azonban lényegesen szebb az órán mutatott megoldás,
  * mivel ott pl. már operátorokat is túlterheltünk, illetve
  * kivételeket is kezeltünk.
  */

struct Receipt {
    string name;
    unsigned int fullPrice; /// A beolvasás egyből a számla végösszegét állítja majd elő
};

enum Status { norm, abnorm };

bool read(Status &st, Receipt &e, ifstream &f)
{
    string line;
    getline(f, line);
    if (f.fail() || line == "") {
        st = abnorm;
    }
    else {
        st = norm;
        istringstream in(line);
        in >> e.name;

        string product;
        int price;
        e.fullPrice = 0;
        while (in >> product >> price) e.fullPrice += price;
    }

    return st == norm;
}

int main()
{
    ifstream x("input.txt");
    if (x.fail()) {
        cerr << "Invalid file name!\n";
        return 1;
    }

    Receipt e;
    Status st;
    int sum = 0;
    while(read(st, e, x)) {
        sum += e.fullPrice;
    }

    cout << "Today's income is " << sum << " Forints." << endl;
    return 0;
}
