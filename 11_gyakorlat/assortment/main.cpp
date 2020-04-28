#include "../library/seqinfileenumerator.hpp"
#include "../library/summation.hpp"
#include <iostream>
#include <string>


using namespace std;

class Assortment : public Summation<int, ostream> {
public:
    Assortment(ostream* f)
        : Summation<int, ostream>::Summation(f)
    {
    }

protected:
    string func(const int& e) const override
    {
        ostringstream os;
        os << e << " ";
        return os.str();
    }
    bool cond(const int& e) const override { return e % 2 == 0; }
};

int main(int argc, char* argv[])
{
    string inputfile_name = (argc >= 2) ? argv[1] : "input.txt";
    string outputfile_name = (argc >= 3) ? argv[2] : "output.txt";

    ofstream f(outputfile_name);
    Assortment pr(&f); // Assortment pr(&cout);
    SeqInFileEnumerator<int> enor(inputfile_name);
    pr.addEnumerator(&enor);

    pr.run();

    return 0;
}
