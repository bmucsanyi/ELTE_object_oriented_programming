#include <iostream>
#include "library/maxsearch.hpp"
#include "library/counting.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/stringstreamenumerator.hpp"
/// Enumerator nem kell, mert az már includeolva van a beincludeolt enumeratorokban

using namespace std;

///3-as lépcső
struct Mark {
    string comment;
    int grade;
    friend istream& operator>>(istream& is, Mark& m);
};

istream& operator>>(istream& is, Mark& m) {
    is >> m.comment >> m.grade;
    return is;
}

class coursePass : public LinSearch<Mark, true> { /// Ha optimista, akkor ideírjuk a true-t
    bool cond(const Mark& e) const override {
        return e.grade > 1;
    }
};

///2-es lépcső
struct Line {
    string name;
    string course;
    bool passed;
    friend istream& operator>>(istream& is, Line& l);
};

istream& operator>>(istream& is, Line& l) {
    string str;
    getline(is, str, '\n');
    stringstream ss(str); /// Stringstreamenumeratorban include-olva van
    ss >> l.name >> l.course;
    StringStreamEnumerator<Mark> enor(ss); /// Mark: milyen adattípust sorol fel?
    coursePass pr;
    pr.addEnumerator(&enor); /// pr = procedure
    pr.run();
    l.passed = pr.found();

    return is;
}

class countPassed : public Counting<Line> {
public:
    countPassed(string name) : name(name) {}
private:
    string name; ///Éppen melyik nevet dolgozom fel

    bool cond(const Line& e) const override { ///Summation.hpp-ben
        return e.passed;
    }
    /////////
    void first() override { }
    //////// Most a procedure.hpp-ben található whilecondot írom felül.
    bool whileCond( const Line& current) const override { ///Mindig ugyanígy kell csinálni! first üres, whileCondban a jelenlegi adattag legyen egyenlő az elmentett adattaggal.
        return name == current.name;
    }
};

///1-es lépcső
struct Student {
    string name;
    int numberOfPassed;
};

class StudentEnumerator : public Enumerator<Student> {
private:
    Student elem;
    bool _end; ///Ezzel helyettesítjük a Status enumot.
    SeqInFileEnumerator<Line>* f;
public:
    StudentEnumerator(const string& fileName) { f = new SeqInFileEnumerator<Line>(fileName); }
    void first() override { f->first(); next(); } ///Beolvasunk egyet, meghívjuk a nextet.
    void next() override;
    bool end() const override { return _end; }
    Student current() const override { return elem; }
};

void StudentEnumerator::next() {
    /// Egyedi felsoroló, addig olvas, amíg ugyanaz a név. First nélküli! -> Ez annak a progtételnek a feladata, amelyet felhasznál ez a next ->countPassed
    if ((_end = f->end())) return;

    elem.name = f->current().name;
    countPassed cp(elem.name);
    cp.addEnumerator(f);
    cp.run();
    elem.numberOfPassed = cp.result();
}

class minPassed : public MaxSearch<Student, int, Less<int>> { /// A Less-nek ugyanaz a sablonparamétere mindig, mint a max másodikja!
    int func(const Student& e) const override {
        return e.numberOfPassed;
    }
};

int main() {
    /// File-ból olvasunk, úgyhogy a try-catch használata kötelező! Üres file kezelése is kötelező! A maxker úgy van megírva, mint egy feltmaxker. Tehát van found adattagja, ami nem üres fájl esetén mindig igaz, üres file esetén hamis marad.
    try {
        StudentEnumerator enor("input.txt");
        minPassed pr;
        pr.addEnumerator(&enor);
        pr.run();

        if (pr.found()) cout << "The student who passed the minimal number of courses: " << pr.optElem().name << ". (" << pr.opt() << " courses)" << endl;

    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cerr << "File not found.\n";
        exit(1);
    }
}

/// Ha kiválogatás kell, akkor az ostreames summation-t használjuk kiíratáshoz
/// Zh gyakorlásra kitűnő a második beadandók második részeinek gyakorlásai
