#include <iostream>
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/linsearch.hpp"

using namespace std;

// For grade 3: Find a contestant who participated in high jump, and whose best place is a silver medal.
// Also print the school the contestant is from, and the number of silver medals they've earned.

struct Contest /// enumerated by stringstream~
{
    string name;
    int rank;
    friend istream &operator>>(istream &is, Contest &c)
    {
        is >> c.name >> c.rank;
        return is;
    }
};

struct sumResult
{
    int bestRank;   /// max->min
    bool highJump;  /// lin search
    int noOfSilver; /// counting

    sumResult() {}
    sumResult(int bR, bool hJ, int nOS) : bestRank(bR), highJump(hJ), noOfSilver(nOS) {}
};

class readContestant : public Summation<Contest, sumResult>
{
    sumResult func(const Contest &e) const override
    {
        return sumResult(e.rank, e.name == "highjump", e.rank == 2 ? 1 : 0);
    }
    sumResult neutral() const override
    {
        return sumResult(INT_MAX, false, 0);
    }
    sumResult add(const sumResult &a, const sumResult &b) const override
    {
        return sumResult(a.bestRank < b.bestRank ? a.bestRank : b.bestRank, a.highJump || b.highJump, a.noOfSilver + b.noOfSilver);
    }
};

struct Contestant /// enumerated by seqInFile~
{
    string name;
    string school;
    int bestRank;
    bool highJump;
    int noOfSilver;

    friend istream &operator>>(istream &is, Contestant &c)
    {
        string line;
        getline(is, line, '\n');
        stringstream ss(line);
        ss >> c.name >> c.school; ///rest of ss contains Contests
        StringStreamEnumerator<Contest> ssenor(ss);

        readContestant pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        c.bestRank = pr.result().bestRank;
        c.highJump = pr.result().highJump;
        c.noOfSilver = pr.result().noOfSilver;
        return is;
    }
};

class MySearch : public LinSearch<Contestant>
{
    bool cond(const Contestant &e) const override
    {

        return (e.bestRank == 2 && e.highJump);
    }
};

int main()
{
    try
    {
        string fileName = "input.txt";
        cout << "Student in highjump with silver as best:\n\n";
        SeqInFileEnumerator<Contestant> enor(fileName);
        MySearch pr;
        pr.addEnumerator(&enor);
        pr.run();
        if (pr.found())
            cout << pr.elem().name << " from " << pr.elem().school << " with " << pr.elem().noOfSilver << " silvers.\n";
        else
            cout << "There is no such contestant.\n";
    }
    catch (SeqInFileEnumerator<Contestant>::Exceptions err)
    {
        cout << "File not found!\n";
        return 1;
    }
    return 0;
}
