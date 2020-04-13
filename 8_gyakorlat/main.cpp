#include "Customer.h"
#include <iostream>

using namespace std;

/** Egy kisvárosi üzlet élelmiszer részlegből és műszaki részlegből áll. A vásárlók egy bevásárlólistára
  * felírták azon termékek neveit, amit megvennének. Az üzletben a listájukon szereplő termékeket keresik:
  * először az élelmiszer részlegen nézik végig a teljes bevásárlólistát, és a megtalált termékeket magukhoz
  * veszik (beteszik a kosarukba), majd a műszaki részlegen ezt megismétlik, de megfontoltabban: ha egy (a
  * bevásárlólistán szereplő) áruból több is van a részlegen, akkor a legolcsóbbat választják.
  */

int main()
{
    try {
        Customer c1("Balint", "c1.txt");
        Shop shop1("food.txt", "tech.txt");
        c1.purchase(shop1);
        cout << c1 << endl;
    } catch (Customer::Exception e) {
        if (e == Customer::OPEN_ERROR) {
            cout << "Customer: file open error.\n";
            return 1;
        }
    } catch (Department::Exception e) {
        if (e == Department::OPEN_ERROR)
            cout << "Department: file open error.\n";
        else
            cout << "Department: invalid index.\n";
        return 2;
    }
    return 0;
}
