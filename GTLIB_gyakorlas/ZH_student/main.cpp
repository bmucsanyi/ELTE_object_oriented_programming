#include <iostream>
///3. szint
#include "library/linsearch.hpp"
#include "library/stringstreamenumerator.hpp"

///2. szint
#include "library/counting.hpp"
#include "library/seqinfileenumerator.hpp"

///1. Szint
#include "library/maxsearch.hpp"

using namespace std;

///3. szint
struct Mark {
    string comment;
    int grade;
    friend istream& operator>>(istream& is, Mark& m);
};

istream& operator>>(istream& is, Mark& m)
{
    is >> m.comment >> m.grade;
    return is;
}

class IsPassed : public LinSearch<Mark, true> {
    bool cond(const Mark& e) const override
    {
        return e.grade > 1;
    }
};

///2. szint
struct Line {
    string name;
    string course;
    bool passed;
    friend istream& operator>>(istream& is, Line& l);
};

istream& operator>>(istream& is, Line& l)
{
    string line;
    getline(is, line, '\n');
    stringstream ss(line);
    ss >> l.name >> l.course;

    IsPassed pr;
    StringStreamEnumerator<Mark> enor(ss);
    pr.addEnumerator(&enor);
    pr.run();

    l.passed = pr.found();

    return is;
}

class CountPassed : public Counting<Line> {
public:
    CountPassed(const string& name) : name(name) {}

private:
    void first() override { }
    bool whileCond(const Line& current) const override { return current.name == name; }
    bool cond(const Line& e) const override { return e.passed; }
    string name;
};

///1. szint
struct Student {
    string name;
    int numberOfPassed;
};

class StudentEnumerator : public Enumerator<Student> {
public:
    StudentEnumerator(const string& fileName) { enor = new SeqInFileEnumerator<Line>(fileName); }
    void first() override
    {
        enor->first();
        next();
    }
    void next() override;
    bool end() const override { return _end; }
    Student current() const override { return elem; }

private:
    SeqInFileEnumerator<Line>* enor;
    bool _end;
    Student elem;
};

void StudentEnumerator::next()
{
    if ((_end = enor->end()))
        return;

    elem.name = enor->current().name; /// Az enor-ban az előző lépés name-je van benne, ami pont az, ami nekünk kell, hiszen akkor áll le, amikor a név már nem egyezik.

    CountPassed cp(elem.name);
    cp.addEnumerator(enor);
    cp.run();

    elem.numberOfPassed = cp.result();
}

class MinPassed : public MaxSearch<Student, int, Less<int>> {
private:
    int func(const Student& e) const override
    {
        return e.numberOfPassed;
    }
};

int main()
{
    try {
        StudentEnumerator enor("input.txt");
        MinPassed pr;
        pr.addEnumerator(&enor);
        pr.run();
        if (pr.found()) {
            cout << pr.optElem().name << " passed the least courses. (" << pr.opt() << ")\n";
        } else {
            cout << "Empty file!\n";
        }
    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cerr << "File not found.\n";
        exit(1);
    }
}
