#include "../library/counting.hpp"
#include "../library/enumerator.hpp"
#include "../library/linsearch.hpp"
#include "../library/maxsearch.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/stringstreamenumerator.hpp"
#include <iostream>


/// Fájlban: hallgató egy szavas neve + tárgy egy szavas neve + (komment,jegy) párosok, amiket a hallgató abból a tárgyból szerzett
/// egy hallgatóhoz több tárgy is tartozik
/// a fájl hallgatók szerint rendezett

/// Kérdés: Melyik hallgató végezte el a legkevesebb tárgyat? (Egy hallgató elvégzett egy tárgyat, ha abból minden jegye legalább kettes.)
/// Megszámoljuk azokat a tárgyakat, ahol minden jegy leaglább kettes, majd egy minimum-kiválasztás a darabszámra (opt. lin. ker.+ számlálás + min. ker.).
/// Más megoldás is lehetséges, de ebben 3 fajta tételre is rá lehet nézni.

using namespace std;

/// Általánosságban elmondható, hogy minden szint 3 komponensből áll: Struct, Programozási tétel, Felsoroló.

/********************** LEGALSÓ SZINT **********************/

/// (3) - struct
struct Mark {
    string comment;
    int grade;
    friend istream& operator>>(istream& is, Mark& m)
    {
        is >> m.comment >> m.grade;
        return is;
    }
};

/// (3) - programozási tétel
class CoursePass : public LinSearch<Mark, true> {
    bool cond(const Mark& e) const override { return e.grade >= 2; }
};

/// (3) - felsoroló NEM kell, mivel nekünk csak az egyedi felsorolókat kell újraírnunk,
/// ebben az esetben pedig elég egy egyszerű StringStreamEnumerator.

/********************** KÖZÉPSŐ SZINT **********************/

/// (2) - struct
struct Line {
    string name;
    string course;
    bool passed;
    friend istream& operator>>(istream& is, Line& line);
};

istream& operator>>(istream& is, Line& line)
{
    string str;
    getline(is, str);
    stringstream ss(str);
    ss >> line.name >> line.course;
    CoursePass pr;
    StringStreamEnumerator<Mark> enor(ss);
    pr.addEnumerator(&enor);
    pr.run();
    line.passed = pr.found();
    return is;
}

/// (2) - programozási tétel
class countPassed : public Counting<Line> {
private:
    string _name;

public:
    countPassed(const string& name)
        : _name(name)
    {
    }

protected:
    bool cond(const Line& e) const override { return e.passed; }
    bool whileCond(const Line& e) const override { return e.name == _name; }
    void first() override {}
};

/// (2) - felsoroló NEM kell, mivel nekünk csak az egyedi felsorolókat kell újraírnunk,
/// ebben az esetben pedig elég egy egyszerű SeqInFileEnumerator.

/********************** LEGFELSŐ SZINT **********************/

/// (1) - struct
struct Student {
    string name;
    int noOfPassed;
};

/// (1) - felsoroló
class StudentEnumerator : public Enumerator<Student> {
private:
    SeqInFileEnumerator<Line>* _f;
    Student _student;
    bool _end;

public:
    StudentEnumerator(const string& fname) { _f = new SeqInFileEnumerator<Line>(fname); }
    ~StudentEnumerator() { delete _f; }
    void first() override
    {
        /// Előreolvasásos technika (egyedi felsoroló)
        _f->first();
        next();
    }
    void next() override; /// Hosszú, nem az osztályon belül írjuk meg.
    Student current() const override { return _student; }
    bool end() const override { return _end; }
};

void StudentEnumerator::next()
{
    if ((_end = _f->end()))
        return;
    _student.name = _f->current().name;
    countPassed pr(_student.name);
    pr.addEnumerator(_f);
    pr.run();
    _student.noOfPassed = pr.result();
}

/// (1) - programozási tétel
class minPassing : public MaxSearch<Student, int, Less<int>> {
    virtual int func(const Student& e) const override { return e.noOfPassed; }
};

int main(int argc, char* argv[])
{
    string inputfile_name = (argc == 1) ? "input.txt" : argv[1];

    try {
        minPassing pr;
        StudentEnumerator enor(inputfile_name);
        pr.addEnumerator(&enor);
        pr.run();
        cout << "The students who passed the least courses: " << pr.optElem().name << " (" << pr.opt() << " courses).\n";
    } catch (SeqInFileEnumerator<Line>::Exceptions exc) {
        cout << "File not found.\n";
    }
    return 0;
}
