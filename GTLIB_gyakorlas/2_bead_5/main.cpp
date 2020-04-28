#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/counting.hpp"
#include "library/maxsearch.hpp"

using namespace std;

/// 2.szint
struct Line {
    string raceID;
    friend istream& operator>>(istream& is, Line& l);
};

istream& operator>>(istream& is, Line& l) {
    string line;
    string tmp;
    getline(is, line, '\n');
    stringstream ss(line);
    ss >> tmp >> l.raceID;

    return is;
}

class CountFishers : public Counting<Line> {
public:
    CountFishers(const string& raceID) : raceID(raceID) {}
private:
    string raceID;
    void first() override {}
    bool whileCond(const Line& current) const { return current.raceID == raceID; }
};

/// 1.szint
struct Race {
    string raceID;
    int fisherCount;
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
    SeqInFileEnumerator<Line>* f;
    Race elem;
};

void RaceEnumerator::next() {
    if ((_end = f->end())) return;

    elem.raceID = f->current().raceID;

    CountFishers pr(elem.raceID);
    pr.addEnumerator(f);
    pr.run();

    elem.fisherCount = pr.result();
}

class MaxFisherCount : public MaxSearch<Race, int> {
    int func(const Race& e) const override { return e.fisherCount; }
};

int main() {
    try {
        RaceEnumerator enor("input.txt");
        MaxFisherCount pr;
        pr.addEnumerator(&enor);
        pr.run();

        if (pr.found()) cout << "The most fishes per race were caught on " << pr.optElem().raceID << ". (" << pr.opt() << ")\n";
        else cout << "Empty file!\n";
    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cerr << "File not found!\n";
        exit(69);
    }
}
