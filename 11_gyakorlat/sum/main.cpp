#include "../library/seqinfileenumerator.hpp"
#include "../library/summation.hpp"
#include <iostream>


using namespace std;

class MySum : public Summation<int> {
protected:
    int neutral() const override { return 0; }
    int add(const int& a, const int& b) const override { return a + b; }
    int func(const int& e) const override { return e; }
};

int main(int argc, char* argv[])
{
    string inputfile_name = (argc == 1) ? "input.txt" : argv[1];

    MySum pr;
    SeqInFileEnumerator<int> enor(inputfile_name);
    pr.addEnumerator(&enor);

    pr.run();

    cout << "Osszeg: " << pr.result() << endl;

    return 0;
}
