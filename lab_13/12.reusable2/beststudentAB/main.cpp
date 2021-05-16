#include <iostream>
///#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"

using namespace std;

struct Mark
{
    string name;
    int mark;
    friend istream &operator>>(istream &is, Mark &m);
};

istream &operator>>(istream &is, Mark &m)
{
    is >> m.name >> m.mark;
    return is;
}

struct Result // members are public by default
{
    int sum;
    int count;

    Result() {}
    Result(int s, int c) : sum(s), count(c) {}
};

class Average : public Summation<Mark, Result>
{
private:
    string _name;

public:
    Average(const string &name) : _name(name) {}

protected:
    Result func(const Mark &e) const override { return Result(e.mark, 1); }
    Result neutral() const override { return Result(0, 0); }
    Result add(const Result &a, const Result &b) const override
    {
        return Result(a.sum + b.sum, a.count + b.count);
    }
    bool whileCond(const Mark &e) const override { return e.name == _name; }
    void first() override {} // normally calls the enumerator's first method
};

struct Student
{
    string name;
    double avr;
};

class StudentEnumerator : public Enumerator<Student>
{
private:
    SeqInFileEnumerator<Mark> *_f; // read(); next();
    Student _student;
    bool _end;

public:
    StudentEnumerator(const string &fname) { _f = new SeqInFileEnumerator<Mark>(fname); }
    ~StudentEnumerator() { delete _f; }
    void first() override
    {
        _f->first();
        next();
    }
    void next() override;
    Student current() const override { return _student; }
    bool end() const override { return _end; }
};

void StudentEnumerator::next()
{
    if ((_end = _f->end()))
        return;
    _student.name = _f->current().name;
    Average pr(_student.name);
    pr.addEnumerator(_f);

    pr.run();

    if (pr.result().count > 0)
        _student.avr = double(pr.result().sum) / pr.result().count;
    else
        _student.avr = 0.0;
}

class BestStudent : public MaxSearch<Student, double>
{
protected:
    double func(const Student &e) const override { return e.avr; }
};

int main()
{
    try
    {
        BestStudent pr;
        StudentEnumerator myenor("empty.txt");
        pr.addEnumerator(&myenor);

        pr.run();
        if (pr.found())
            cout << pr.optElem().name << " is the best student.\n";
        else
            cout << "The file is empty!\n";
    }
    catch (SeqInFileEnumerator<Mark>::Exceptions exc)
    {
        cout << "File does not exist!\n";
        return 1;
    }
    return 0;
}
