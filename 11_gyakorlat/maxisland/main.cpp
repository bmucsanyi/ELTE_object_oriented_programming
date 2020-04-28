#include <iostream>
#include <vector>
#include "../library/seqinfileenumerator.hpp"
#include "../library/maxsearch.hpp"
#include "../library/counting.hpp"
#include "../library/selection.hpp"

using namespace std;

class MyMax : public MaxSearch<int>
{
protected:
    int func(const int &e) const { return e; }
};

class IslandEnumerator : public Enumerator<int>
{
private:
    SeqInFileEnumerator<int> *_f;
    int _length;
    bool _end;
public:
    IslandEnumerator(const string &fname){
        _f = new SeqInFileEnumerator<int>(fname);
    }
    ~IslandEnumerator(){ delete _f; }
    void first() override { _f->first(); next(); }
    void next() override;
    int current() const override { return _length; }
    bool end() const override { return _end; }
};

class CrossSee : public Selection<int>
{
protected:
    void first() override {}
    bool cond(const int &e) const override { return _enor->end() || e!=0; }
};

class IslandLength : public Counting<int>
{
protected:
    void first() override {}
    bool whileCond(const int &e) const override { return e>0; }
};

void IslandEnumerator::next()
{
    CrossSee pr1;
    pr1.addEnumerator(_f);
    pr1.run();

    if( (_end = _f->end()) ) return;

    IslandLength pr2;
    pr2.addEnumerator(_f);
    pr2.run();
    _length = pr2.result();
}

int main(int argc, char* argv[])
{
    string inputfile_name = (argc==1)? "input.txt" : argv[1];

    MyMax pr;
    IslandEnumerator enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();

    cout << "Leghosszabb sziget hossza " << pr.opt() << endl;
    return 0;
}
