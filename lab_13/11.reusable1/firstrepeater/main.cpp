#include <iostream>
#include <vector>
#include "library/seqinfileenumerator.hpp"
#include "library/intervalenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/summation.hpp"
#include "library/intervalenumerator.hpp"

// Which number is repeated first?

using namespace std;

class Copy : public Summation<int, vector<int>>
{
public:
    int func(const int &e) const override { return e; }
};

class InnerSearch : public LinSearch<int>
{
private:
    vector<int> _x;
    int _i;

public:
    InnerSearch(vector<int> x, int i) : _x(x), _i(i) {}
    bool cond(const int &j) const override { return _x[_i] == _x[j]; }
};

class OuterSearch : public LinSearch<int>
{
private:
    vector<int> _x;

public:
    OuterSearch(vector<int> x) : _x(x) {}
    bool cond(const int &i) const override
    {
        InnerSearch pr(_x, i);
        IntervalEnumerator enor(0, i - 1);
        pr.addEnumerator(&enor);
        pr.run();
        return pr.found();
    }
};

int main()
{
    /// Filling the array from file
    vector<int> x;
    Copy pr1;
    SeqInFileEnumerator<int> enor1("input.txt");
    pr1.addEnumerator(&enor1);
    pr1.run();
    x = pr1.result();

    /// Searching for the first repeater
    OuterSearch pr2(x);
    IntervalEnumerator enor2(1, x.size() - 1);
    pr2.addEnumerator(&enor2);
    pr2.run();

    if (pr2.found())
        cout << "First repeater is: " << x[pr2.elem()] << "\n";
    else
        cout << "There is no repeating item.\n";
    return 0;
}
