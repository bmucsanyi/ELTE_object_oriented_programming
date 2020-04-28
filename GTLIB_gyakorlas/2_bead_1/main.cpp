#include <iostream>
#include "library/stringstreamenumerator.hpp"
#include "library/counting.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/maxsearch.hpp"

using namespace std;

///3. szint
struct Fish {
    string type;
    double weight;
    friend istream& operator>>(istream& is, Fish& f);
};

istream& operator>>(istream& is, Fish& f) {
    is >> f.type >> f.weight;
    return is;
}

class CountFishes : public Counting<Fish> {};

///2. szint
struct Line {
    string raceId;
    int numberOfFishes;
    friend istream& operator>>(istream& is, Line& l);
};

istream& operator>>(istream& is, Line& l) {
    string line;
    string tmp;
    getline(is, line, '\n');
    stringstream ss(line);
    ss >> tmp >> l.raceId;

    StringStreamEnumerator<Fish> enor(ss);
    CountFishes pr;
    pr.addEnumerator(&enor);
    pr.run();

    l.numberOfFishes = pr.result();
    return is;
}

class SumFishes : public Summation<Line, int> {
public:
    SumFishes(const string& raceId) : raceId(raceId) {}
private:
    string raceId;
    int func(const Line& e) const override { return e.numberOfFishes; }
    int neutral() const override { return 0; }
    int add( const int& a, const int& b) const override { return a + b; }
    void first() override { }
    bool whileCond(const Line& current) const override { return current.raceId == raceId; }
};

///1. szint
struct Race {
    string raceId;
    int allFishes;
};

class RaceEnumerator : public Enumerator<Race> {
public:
    RaceEnumerator(const string& fileName) { f = new SeqInFileEnumerator<Line>(fileName); }
    void first() override { f->first(); next(); }
    void next() override;
    bool end() const override { return _end; }
    Race current() const override { return elem; }
    ~RaceEnumerator() { delete f; }
private:
    bool _end;
    Race elem;
    SeqInFileEnumerator<Line>* f;
};

void RaceEnumerator::next() {
    if ((_end = f->end())) return;

    elem.raceId = f->current().raceId;

    SumFishes sf(elem.raceId);
    sf.addEnumerator(f);
    sf.run();

    elem.allFishes = sf.result();
}

class MaxNumberOfFishes : public MaxSearch<Race, int> {
    int func(const Race& e) const override { return e.allFishes; }
};

int main() {
    try {
        RaceEnumerator enor("input.txt");

         MaxNumberOfFishes pr;
         pr.addEnumerator(&enor);
         pr.run();

         if (pr.found()) {
            cout << "The race " << pr.optElem().raceId << " was the one with the highest fish count. (" << pr.opt() << ")" << endl;
         }
         else cout << "Empty file!\n";
    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cerr << "File not found.\n";
        exit(1);
    }
}
