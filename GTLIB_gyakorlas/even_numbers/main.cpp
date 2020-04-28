#include <iostream>
#include "library/stringstreamenumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/counting.hpp"

using namespace std;

class CountEven : public Counting<int> {
    bool cond(const int& e) const override { return e % 2 == 0; }
};

struct Line {
    int numberOfEven;
    friend istream& operator>>(istream& is, Line& l);
};

istream& operator>>(istream& is, Line& l) {
    string str;
    getline(is, str);
    stringstream ss(str);
    StringStreamEnumerator<int> enor(ss);

    CountEven pr;
    pr.addEnumerator(&enor);
    pr.run();

    l.numberOfEven = pr.result();

    return is;
}

class Write : public Summation<Line, ostream> {
public:
    Write(ostream* o) : Summation(o) {}
private:
    std::string func(const Line& e) const override {
        stringstream ss;
        ss << e.numberOfEven << "\n";
        return ss.str();
    }
};

int main() {
    try {
        SeqInFileEnumerator<Line> enor("input.txt");
        Write pr(&cout);
        pr.addEnumerator(&enor);
        pr.run();
    } catch (SeqInFileEnumerator<Line>::Exceptions err) {
        cerr << "File not found.\n";
        exit(1);
    }
}
