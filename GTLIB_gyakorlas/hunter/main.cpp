#include <iostream>
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/linsearch.hpp"

using namespace std;

///3. szint
struct Animal {
    string name;
    double weight;
    friend istream& operator>>(istream& is, Animal& a);
};

istream& operator>>(istream& is, Animal& a) {
    is >> a.name >> a.weight;
    return is;
}

class CaughtBearRace : public Summation<Animal, bool> {
    bool func(const Animal& e) const override { return e.name == "bear"; }
    bool neutral() const override { return false; }
    bool add( const bool& a, const bool& b) const override { return a || b; }
};

///2. szint
struct Line {
    string hunterName;
    bool bear;
    friend istream& operator>>(istream& is, Line& l);
};

istream& operator>>(istream& is, Line& l) {
    string line;
    string tmp;
    getline(is, line, '\n');
    stringstream ss(line);
    ss >> l.hunterName >> tmp;

    StringStreamEnumerator<Animal> enor(ss);
    CaughtBearRace pr;
    pr.addEnumerator(&enor);
    pr.run();

    l.bear = pr.result();
    return is;
}

class CaughtBear : public Summation<Line, bool> {
public:
    CaughtBear(string hunterName) : hunterName(hunterName) {}
private:
    string hunterName;
    bool func(const Line& e) const override { return e.bear; }
    bool neutral() const override { return false; }
    bool add( const bool& a, const bool& b) const override { return a || b; }
    void first() override { }
    bool whileCond(const Line& current) const override { return current.hunterName == hunterName; }
};

///1. szint
struct Hunter {
    string hunterName;
    bool bear;
};

class HunterEnumerator : public Enumerator<Hunter> {
public:
    HunterEnumerator(string fileName) { f = new SeqInFileEnumerator<Line>(fileName); }
    void first() override { f->first(); next(); }
    void next() override;
    bool end() const override { return _end; }
    Hunter current() const override { return elem; }
    ~HunterEnumerator() { delete f; }
private:
    SeqInFileEnumerator<Line>* f;
    bool _end;
    Hunter elem;
};

void HunterEnumerator::next() {
    if ((_end = f->end())) return;

    elem.hunterName = f->current().hunterName;

    CaughtBear pr(elem.hunterName);
    pr.addEnumerator(f);
    pr.run();

    elem.bear = pr.result();
}

class AllShotBear : public LinSearch<Hunter, true> {
    bool cond(const Hunter& e) const override { return e.bear; }
};

int main() {
    try {
        HunterEnumerator enor("input.txt");
        AllShotBear pr;
        pr.addEnumerator(&enor);
        pr.run();

        if (pr.found()) cout << "Every hunter shot bear in this season." << endl;
        else cout << "Not every hunter shot bear in this season." << endl;
    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cerr << "File not found!\n";
        exit(1);
    }
}
