/// Megoldás a mintazh-hoz. Letölthető: people.inf.elte.hu/gt/oep

#include <iostream>
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/maxsearch.hpp"

using namespace std;

/// 3. szint
struct Observation {
    string date;
    int weight;
    int distance;
    friend istream& operator>>(istream& is, Observation& o);
};

istream& operator>>(istream& is, Observation& o) {
    is >> o.date >> o.weight >> o.distance;
    return is;
}

struct WeightPlusNear { /// Összegzés tételhez
    WeightPlusNear(int weight = 0, bool near = false) : weight(weight), near(near) {}
    int weight;
    bool near;
};

class SumWeightNear : public Summation<Observation, WeightPlusNear> {
    WeightPlusNear func(const Observation& e) const override { return WeightPlusNear(e.weight, e.distance < 3); }
    WeightPlusNear neutral() const override { return WeightPlusNear(); }
    WeightPlusNear add( const WeightPlusNear& a, const WeightPlusNear& b) const override { return WeightPlusNear(b.weight, (a.near || b.near)); }
};

/// 2.szint
struct Line {
    string blackHoleId;
    int heaviestWeight;
    bool near;
    friend istream& operator>>(istream& is, Observation& o);
};

istream& operator>>(istream& is, Line& l) {
    string line;
    string tmp;
    getline(is, line, '\n');
    stringstream ss(line);
    ss >> l.blackHoleId >> tmp;

    StringStreamEnumerator<Observation> enor(ss);
    SumWeightNear pr;
    pr.addEnumerator(&enor);
    pr.run();

    l.heaviestWeight = pr.result().weight;
    l.near = pr.result().near;

    return is;
}

struct Average {
    Average(int sum = 0, int count = 0, bool near = true) : sum(sum), count(count), near(near) {}
    int sum;
    int count;
    bool near;
};

class SumLines : public Summation<Line, Average> {
public :
    SumLines(const string& blackHoleId) : blackHoleId(blackHoleId) {}
private:
    string blackHoleId;
    Average func(const Line& e) const override { return Average(e.heaviestWeight, 1, e.near); }
    Average neutral() const override { return Average(); }
    Average add( const Average& a, const Average& b) const override { return Average(a.sum+b.sum, a.count+b.count, (a.near && b.near)); }
    void first() override { }
    bool whileCond(const Line& current) const override { return current.blackHoleId == blackHoleId; }
};

/// 1.szint
struct BlackHole {
    string blackHoleId;
    double averageWeight;
    bool near;
};

class BlackHoleEnumerator : public Enumerator<BlackHole> {
public:
    BlackHoleEnumerator(const string& fileName) { f = new SeqInFileEnumerator<Line>(fileName); }
    void first() override { f->first(); next(); }
    void next() override;
    bool end() const override { return _end; }
    BlackHole current() const override { return elem; }
    ~BlackHoleEnumerator() { delete f; }
private:
    SeqInFileEnumerator<Line>* f;
    bool _end;
    BlackHole elem;
};

void BlackHoleEnumerator::next() {
    if ((_end = f->end())) return;

    elem.blackHoleId = f->current().blackHoleId;

    SumLines pr(elem.blackHoleId);
    pr.addEnumerator(f);
    pr.run();

    if (pr.result().count == 0) elem.averageWeight = 0;
    else elem.averageWeight = double(pr.result().sum) / pr.result().count;

    elem.near = pr.result().near;
}

class HeaviestBelow3 : public MaxSearch<BlackHole, double> {
    double func(const BlackHole& e) const override { return e.averageWeight; }
    bool cond(const BlackHole& e) const override { return e.near;}
};

int main() {
    try {
        BlackHoleEnumerator enor("input.txt");
        HeaviestBelow3 pr;
        pr.addEnumerator(&enor);
        pr.run();

        if (pr.found()) cout << "The heaviest blackhole, which was observed nearer than 3 million light years at least once by every station: " << pr.optElem().blackHoleId << " (" << pr.opt() << " Suns).\n";
        else cout << "There are no black holes with the desired condition.\n";
    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cerr << "File open error!\n";
        exit(1);
    }
}

/*
CX896 SOJUZ 1978.09.22 60 6 1999.04.17 85 4 2003.11.03 90 2
CX896 NASA 1984.03.12 68 5 2003.11.23 91 2
SH231 SOJUZ 1986.10.17 4 2 2003.04.17 9000 4 2008.11.03 6 2
SH231 VALAMI 1986.11.17 4 5 2003.04.17 150000 4 2008.11.03 6 5
*/