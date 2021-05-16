#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/linsearch.hpp"

using namespace std;

struct Contest
{
    string name;
    int rank;
    friend istream &operator>>(istream &is, Contest &c)
    {
        is >> c.name >> c.rank;
        return is;
    }
};

class highJumpEntry : public LinSearch<Contest>
{
    bool cond(const Contest &e) const override
    {
        return e.name == "highjump";
    }
};

struct Contestant
{
    string name;
    string school;
    bool highJump;
    friend istream &operator>>(istream &is, Contestant &c)
    {
        string line;
        getline(is, line, '\n');
        stringstream ss(line);
        ss >> c.name >> c.school;
        StringStreamEnumerator<Contest> ss_enor(ss);
        highJumpEntry pr;
        pr.addEnumerator(&ss_enor);
        pr.run();
        c.highJump = pr.found();
        return is;
    }
};

struct School
{
    string name;
    unsigned int highJumpCounter;
    unsigned int studentCounter;

    School() : highJumpCounter(0), studentCounter(0), name("") {}
    School(const string &n, unsigned int hjc, unsigned int sc) : highJumpCounter(hjc), studentCounter(sc), name(n) {}
};

class schoolResult : public Summation<Contestant, School>
{
public:
    schoolResult(const string &schoolName) : _schoolName(schoolName) {}

private:
    string _schoolName;

    School func(const Contestant &e) const override
    {
        return School(e.school, e.highJump ? 1 : 0, 1);
    }
    School neutral() const override { return School(); }
    School add(const School &a, const School &b) const override
    {
        return School(b.name, a.highJumpCounter + b.highJumpCounter, a.studentCounter + b.studentCounter);
    }

    void first() override {}
    bool whileCond(const Contestant &current) const override
    {
        return current.school == _schoolName;
    }
};

class SchoolEnumerator : public Enumerator<School>
{
private:
    SeqInFileEnumerator<Contestant> *_f;
    School _school;
    bool _end;

    bool _empty;

public:
    SchoolEnumerator(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<Contestant>(fname); }
    ~SchoolEnumerator() { delete _f; }
    void first() override
    {
        _f->first();
        next();
        if (!end())
            _empty = false;
    }
    void next() override;
    School current() const override { return _school; }
    bool end() const override { return _end; }
    bool getEmpty() const { return _empty; }
};

void SchoolEnumerator::next()
{
    if (_end = _f->end())
        return;
    _school.name = _f->current().school;
    schoolResult pr(_school.name);
    pr.addEnumerator(_f);
    pr.run();
    _school = pr.result();
}

class Write : public Summation<School, ostream>
{
public:
    Write(ostream *o) : Summation<School, ostream>(o) {}

private:
    std::string func(const School &e) const override
    {
        ostringstream oss(e.name);
        oss << e.name << ", number of high jump entries: " << e.highJumpCounter << ", number of students: " << e.studentCounter << endl;
        return oss.str();
    }
    bool cond(const School &e) const override
    {
        return e.highJumpCounter > 9;
    }
};

int main(int argc, char **argv)
{
    try
    {
        string fname;
        if (argc > 1)
            fname = argv[1];
        else
            fname = "input.txt";
        cout << "Schools with at least 10 high jump entries:\n\n";
        SchoolEnumerator enor(fname);
        Write pr(&cout);
        pr.addEnumerator(&enor);
        pr.run();
        if (enor.getEmpty())
            cout << "There is none.\n";
    }
    catch (SeqInFileEnumerator<Contestant>::Exceptions err)
    {
        cout << "File not found!\n";
        return 1;
    }
    return 0;
}
