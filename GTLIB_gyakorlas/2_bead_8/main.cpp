#include <iostream>
#include "library/counting.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"
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

class CountCarps : public Counting<Fish> {
    bool cond(const Fish& e) const override {
        return e.type == "Ponty";
    }
};

///2. szint
struct Line {
    string fisherName;
    int carpInRace;
    friend istream& operator>>(istream& is, Line& l);
};

istream& operator>>(istream& is, Line& l) {
    string line;
    string tmp;
    getline(is, line, '\n');
    stringstream ss(line);
    ss >> l.fisherName >> tmp;

    StringStreamEnumerator<Fish> enor(ss);
    CountCarps pr;
    pr.addEnumerator(&enor);
    pr.run();

    l.carpInRace = pr.result();

    return is;
}

class SumCarps : public Summation<Line, int> {
public:
    SumCarps(const string& name) : name(name) {}
private:
    string name;
    int func(const Line& e) const override { return e.carpInRace; }
    int neutral() const override { return 0; }
    int add( const int& a, const int& b) const override { return a + b; }
    void first() override { }
    bool whileCond(const Line& current) const { return current.fisherName == name; }
};

///1. szint
struct Fisher {
    string name;
    int carpNum;
};

class FisherEnumerator : public Enumerator<Fisher> {
public:
    FisherEnumerator(const string& fileName) { f = new SeqInFileEnumerator<Line>(fileName); }
    void first() override { f->first(); next(); }
    void next() override;
    bool end() const override { return _end; }
    Fisher current() const override { return elem; }
    ~FisherEnumerator() { delete f; }
private:
    SeqInFileEnumerator<Line>* f;
    bool _end;
    Fisher elem;
};

void FisherEnumerator::next() {
    if ((_end = f->end())) return;

    elem.name = f->current().fisherName;

    SumCarps sc(elem.name);
    sc.addEnumerator(f);
    sc.run();

    elem.carpNum = sc.result();
}

class MaxCarps : public MaxSearch<Fisher, int> {
    int func(const Fisher& e) const override {
        return e.carpNum;
    }
};

int main() {
    try {
        FisherEnumerator enor("input.txt");
        MaxCarps pr;
        pr.addEnumerator(&enor);
        pr.run();

        if (pr.found()) {
            cout << pr.optElem().name << " caught the most carps. (" << pr.opt() << ").\n";
        }
        else cout << "Empty file.\n";
    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cout << "File not found.\n";
        exit(1);
    }
}
