#include "../library/intervalenumerator.hpp"
#include "../library/summation.hpp"
#include <cmath>
#include <iostream>


using namespace std;

class Factorial : public Summation<int> {
protected:
    int neutral() const override { return 1; }
    int add(const int& a, const int& b) const override { return a * b; }
    int func(const int& e) const override { return e; }
};

int main()
{
    int n;
    cout << "Termeszetes szam: ";
    cin >> n; // ellenőrzés is kell
    Factorial pr;
    IntervalEnumerator enor(2, n);
    pr.addEnumerator(&enor);

    pr.run();

    cout << "Faktorialis: " << pr.result() << endl;

    return 0;
}
