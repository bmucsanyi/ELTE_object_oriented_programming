#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"

using namespace std;

class MySum : public Summation<int>
{
protected:
    int func(const int &e) const override { return e; }
    int neutral() const override { return 0; }
    int add(const int &a, const int &b) const override { return a + b; }
};

int main()
{
    try
    {
        MySum pr;
        SeqInFileEnumerator<int> myenor("input.txt");
        pr.addEnumerator(&myenor);

        pr.run();

        cout << "Sum: " << pr.result() << endl;
    }
    catch (SeqInFileEnumerator<int>::Exceptions exc)
    {
        cout << "File not found!\n";
        return 1;
    }
    return 0;
}
