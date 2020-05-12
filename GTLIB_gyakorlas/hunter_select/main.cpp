#include <iostream>
#include "library/stringstreamenumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"

using namespace std;

/// Soroljuk fel azokat a vadászokat, akik legnehezebb zsákmánya medve volt!

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

class HeaviestInHunt : public MaxSearch<Animal, double> {
    double func(const Animal& e) const override { return e.weight; }
};

///2. szint
struct Line {
    string hunterName;
    Animal heaviestAnimal;
    friend istream& operator>>(istream& is, Line& l);
};

istream& operator>>(istream& is, Line& l) {
    string line;
    string tmp;
    getline(is, line);
    stringstream ss(line);
    ss >> l.hunterName >> tmp;

    StringStreamEnumerator<Animal> enor(ss);
    HeaviestInHunt pr;
    pr.addEnumerator(&enor);
    pr.run();

    l.heaviestAnimal = pr.optElem();

    return is;
}

class HeaviestInSeason : public MaxSearch<Line, double> {
public:
    HeaviestInSeason(const string& hunterName) : hunterName(hunterName) {}
private:
    string hunterName;
    double func(const Line& e) const override { return e.heaviestAnimal.weight; }
    void first() override {}
    bool whileCond(const Line& current) const { return current.hunterName == hunterName; }
};

///1. szint
struct Hunter {
    string hunterName;
    string heaviestType;
};

class HunterEnumerator : public Enumerator<Hunter> {
public:
    HunterEnumerator(const string& fileName) { f = new SeqInFileEnumerator<Line>(fileName); }
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

    HeaviestInSeason pr(elem.hunterName);
    pr.addEnumerator(f);
    pr.run();

    elem.heaviestType = pr.optElem().heaviestAnimal.name;
}

class WriteCond : public Summation<Hunter, ostream> {
public:
    WriteCond(ostream* o) : Summation<Hunter, ostream>(o) {}
private:
    string func(const Hunter& e) const override {
        stringstream ss;
        ss << e.hunterName << "'s heaviest animal was a bear.\n";
        return ss.str();
    }
    bool cond(const Hunter& e) const { return e.heaviestType == "bear"; }
};

int main() {
    try {
        HunterEnumerator enor("input.txt");
        WriteCond pr(&cout);
        pr.addEnumerator(&enor);
        pr.run();
    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cerr << "File not found.\n";
        exit(1);
    }
}
