#include <iostream>
#include <cmath>
#include "library/summation.hpp"
#include "library/intervalenumerator.hpp"

using namespace std;

class Factorial : public Summation<int, int> // Programming theorem
{
protected:
    int func(const int &e) const override { return e; }
    int neutral() const override { return 1; }
    int add(const int &a, const int &b) const override { return a * b; }
};

int main()
{
    int n;
    do
    {
        cout << "Natural number: ";
        cin >> n; /// validation
    } while (n < 0);
    Factorial pr;
    IntervalEnumerator myenor(2, n); // [2, n] = {2, 3, 4, ..., n}
    pr.addEnumerator(&myenor);

    pr.run();

    cout << "Factorial: " << pr.result() << endl;

    return 0;
}
