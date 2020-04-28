#include <iostream>
#include "library/stringstreamenumerator.hpp"
#include "library/counting.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/maxsearch.hpp"

/// 1 neves változat, ugyanis ciklus nélkül nem megoldható a több név.

using namespace std;

/// 3. szint
struct Result {
    string type;
    int placing;
    friend istream& operator>>(istream& is, Result& r);
};

istream& operator>>(istream& is, Result& r) {
    is >> r.type >> r.placing;
    return is;
}

class CountMedals : public Counting<Result> {
    bool cond(const Result& e) const override { return e.placing <= 3; }
};

/// 2. szint
struct Line {
    string schoolID;
    int medalCount;
    friend istream& operator>>(istream& is, Line& l);
};

istream& operator>>(istream& is, Line& l) {
    string line;
    string tmp;
    getline(is, line, '\n');
    stringstream ss(line);

    ss >> tmp >> l.schoolID;

    StringStreamEnumerator<Result> enor(ss);
    CountMedals pr;
    pr.addEnumerator(&enor);
    pr.run();

    l.medalCount = pr.result();

    return is;
}

class SumMedalCount : public Summation<Line, int> {
public:
    SumMedalCount(const string& schoolID) : schoolID(schoolID) {}
private:
    string schoolID;
    int func(const Line& e) const override { return e.medalCount; }
    int neutral() const override { return 0; }
    int add( const int& a, const int& b) const override { return a + b; }
    void first() override { }
    bool whileCond(const Line& current) const { return current.schoolID == schoolID; }
};

/// 1. szint
struct School {
    string schoolID;
    int allMedals;
};

class SchoolEnumerator : public Enumerator<School> {
public:
    SchoolEnumerator(const string& fileName) { f = new SeqInFileEnumerator<Line>(fileName); }
    void first() override { f->first(); next(); }
    void next() override;
    bool end() const override { return _end; }
    School current() const override { return elem; }
    ~SchoolEnumerator() { delete f; }
private:
    bool _end;
    SeqInFileEnumerator<Line>* f;
    School elem;
};

void SchoolEnumerator::next() {
    if ((_end = f->end())) return;

    elem.schoolID = f->current().schoolID;

    SumMedalCount pr(elem.schoolID);
    pr.addEnumerator(f);
    pr.run();

    elem.allMedals = pr.result();
}

class MaxMedalCount : public MaxSearch<School, int> {
    int func(const School& e) const override { return e.allMedals; }
};

int main() {
    try {
        SchoolEnumerator enor("input.txt");
        MaxMedalCount pr;
        pr.addEnumerator(&enor);
        pr.run();

        if (pr.found()) cout << "The school with the highest medal count: " << pr.optElem().schoolID << ". (" << pr.opt() << ")\n";
        else cout << "Empty file!\n";
    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cerr << "File not found!\n";
        exit(1);
    }
}
