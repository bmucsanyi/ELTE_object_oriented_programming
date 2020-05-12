#include "library/arrayenumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include <iostream>
#include <sstream>

using namespace std;

class Concat : public Summation<int, vector<int>> {
    int func(const int& e) const override
    {
        return e;
    }
    bool cond(const int& e) const override
    {
        return e > 0;
    }

public:
    Concat(const vector<int>& v) : Summation<int, vector<int>>(v) {}
};

class Write : public Summation<int, ostream> {
public:
    Write(ostream* os)
        : Summation<int, ostream>(os)
    {
    }

private:
    std::string func(const int& e) const override
    {
        stringstream ss;
        ss << e << " ";
        return ss.str();
    }
};

int main()
{
    try {
        SeqInFileEnumerator<int> enor("input.txt");
        vector<int> v = { 0, 1, 2, 3 };
        Concat pr(v);
        pr.addEnumerator(&enor);
        pr.run();

        ArrayEnumerator<int> arrEnor(&pr.result());
        Write pr2(&cout);
        pr2.addEnumerator(&arrEnor);
        pr2.run();
        cout << "\n";
    } catch (SeqInFileEnumerator<int>::Exceptions exc) {
        cout << "File not found.\n";
    }
    return 0;
}
