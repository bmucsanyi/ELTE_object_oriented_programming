#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include <iostream>


/// Feladat: fileban hallgatók (soronként egy), dolgozat-jegy párok -> Írjuk ki a legjobb átlaggal rendelkező tanulót.

using namespace std;

struct Mark { /// StringStreambõl való beolvasáshoz
    string comment;
    int grade;
    /// Beolvasó operátor
    friend istream& operator>>(istream& is, Mark& m)
    {
        is >> m.comment >> m.grade;
        return is;
    }
};

struct Result { /// Összegzés eredményét tárolja
    int sum;
    int count;
    Result(int sum, int count)
        : sum(sum)
        , count(count)
    {
    }
    Result() { }
};

class Average : public Summation<Mark, Result> {
    Result func(const Mark& e) const override
    {
        return Result(e.grade, 1);
    }
    Result neutral() const override
    {
        return Result(0, 0);
    }
    Result add(const Result& a, const Result& b) const override
    {
        return Result(a.sum + b.sum, a.count + b.count);
    }
};

struct Student {
    string name;
    double avg;
    friend istream& operator>>(istream& is, Student& st)
    {
        string line;
        getline(is, line);
        stringstream ss(line);
        ss >> st.name;
        StringStreamEnumerator<Mark> enor(ss); ///<Mark> = Milyen típusú adatokat tartalmaz?
        Average pr;
        pr.addEnumerator(&enor);
        pr.run();
        Result res = pr.result();
        if (res.count == 0)
            st.avg = 0;
        else
            st.avg = double(res.sum) / res.count; /// Int/int egy egészosztás, ezért kell a konvertálás
        return is;
    }
};

class BestStudent : public MaxSearch<Student, double> { ///3. Param default értéke a 'Greater'
    double func(const Student& e) const override
    {
        return e.avg;
    }
};

int main()
{
    try { /// Szekinfile-nál kötelezõ a try-catch blokk, hiszen dobhat exceptiont
        SeqInFileEnumerator<Student> enor("input.txt");
        BestStudent bs;
        bs.addEnumerator(&enor);
        bs.run();
        if (bs.found()) {
            cout << "Best student: " << bs.optElem().name << endl;
            cout << "Average: " << bs.opt() << endl;
        } else
            cout << "Empty file!\n";
    } catch (SeqInFileEnumerator<Student>::Exceptions e) {
        cout << "File not found.\n";
    }
}
