#include "../library/maxsearch.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/stringstreamenumerator.hpp"
#include "../library/summation.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/// Ki a kurzus legjobb hallgatója? A hallgatók nevét és több részeredményét (0 és 5 közötti jegy) egy-
/// egy sorban adjuk meg.

using namespace std;

/********************** ALSÓ SZINT **********************/

struct Student {
    string name;
    double avr;

    friend istream& operator>>(istream& inp, Student& s);
};

istream& operator>>(istream& inp, Student& s)
{
    string line;
    getline(inp, line);
    stringstream is(line);
    is >> s.name;

    Average pr;
    StringStreamEnumerator<int> enor(is);
    pr.addEnumerator(&enor);

    pr.run();

    s.avr = pr.result().sum / pr.result().count;

    return inp;
}

class BestStudent : public MaxSearch<Student, double> {
protected:
    double func(const Student& e) const override { return e.avr; }
};

/********************** FELSŐ SZINT **********************/

/// (2) - struct
struct Result {
    double sum;
    int count;
    Result() {}
    Result(double s, int c)
        : sum(s)
        , count(c)
    {
    }
};

/// (2) - programozási tétel
class Average : public Summation<int, Result> {
protected:
    Result func(const int& e) const override { return Result(e, 1); }
    Result neutral() const override { return Result(0.0, 0); }
    Result add(const Result& a, const Result& b) const override
    {
        return Result(a.sum + b.sum, a.count + b.count);
    }
};

int main(int argc, char* argv[])
{
    string inputfile_name = (argc == 1) ? "input.txt" : argv[1];

    BestStudent pr;
    SeqInFileEnumerator<Student> enor("input.txt");
    pr.addEnumerator(&enor);

    pr.run();

    if (pr.found()) {
        cout << "A legjobb diak " << pr.optElem().name << ", akinek az atlaga: " << pr.opt() << endl;
    } else
        cout << "Ures a fajl!\n";
    return 0;
}