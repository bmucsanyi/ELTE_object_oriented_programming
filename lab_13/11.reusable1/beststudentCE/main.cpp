#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/summation.hpp"

using namespace std;

struct Result
{
    int sum;
    int count;

    Result(int s, int c) : sum(s), count(c) {}
};

class Average : public Summation<int, Result>
{
protected:
    Result func(const int &e) const override
    {
        return Result(e, 1);
    }
    Result neutral() const override { return Result(0, 0); }
    Result add(const Result &a, const Result &b) const override
    {
        return Result(a.sum + b.sum, a.count + b.count);
    }
};

struct Student ///SeqInFile -> reading operator!!!
{
    string name;
    double avr;

    friend istream &operator>>(istream &inp, Student &s);
};

istream &operator>>(istream &inp, Student &s)
{
    string line;
    getline(inp, line, '\n');
    stringstream is(line);
    is >> s.name; ///in "is", there are only marks after this

    Average pr;
    StringStreamEnumerator<int> enor(is);
    pr.addEnumerator(&enor);

    pr.run();

    if (pr.result().count > 0)
    {
        s.avr = double(pr.result().sum) / pr.result().count;
    }
    else
    {
        s.avr = 0;
    }

    return inp;
}

class BestStudent : public MaxSearch<Student, double>
{
protected:
    double func(const Student &e) const override
    {
        return e.avr;
    }
};

int main()
{
    try
    {
        BestStudent pr;
        SeqInFileEnumerator<Student> myenor("input.txt");
        pr.addEnumerator(&myenor);

        pr.run();

        if (pr.found())
        {
            cout << "Best student is " << pr.optElem().name << ", whose average is: " << pr.opt() << endl;
        }
        else
        {
            cout << "Empty file!\n";
        }
    }
    catch (SeqInFileEnumerator<Student>::Exceptions exc)
    {
        cout << "File does not exist!\n";
        return 1;
    }

    return 0;
}
