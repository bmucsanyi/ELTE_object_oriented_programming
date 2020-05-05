#include <iostream>
#include <string>

using namespace std;

/// Fordítás: g++ -std=c++11 -pedantic -Wall -Wextra derived.cpp -o derived.out

/// OEP elv: egységbe zárás
class Eloleny {
private:
    int kor; /// OEP elv: enkapszuláció, az ember nem éri el
public:
    Eloleny()
        : kor(0) {};
    virtual ~Eloleny() { cout << "Eloleny kiirtva" << endl; }

    virtual string faj() const { return "Elo valami"; };
    void sayHi() { cout << "Szia" << endl; }

    int getkor() const { return kor; };
    void setkor(int k)
    {
        kor = k;
        cout << "A kor mostantol " << k << endl;
    }
};

/// OEP elv: öröklődés
class Ember : public Eloleny {
public:
    ~Ember() { cout << "Ember kiirtva" << endl; }

    /// felüldefiniálás
    /* virtual */ string faj() const override { return "Ember"; };
};

void printFajRossz(Eloleny e) /// mindig Eloleny-t fog kapni
{
    cout << "Faj: " << e.faj() << endl;
}

/// OEP elv: polimorfizmus
void printFajJo(Eloleny& e)
{
    cout << "Faj: " << e.faj() << endl;
}

/*
Parent* child = new Child();
*/

class Shape {
public:
    /// kommenteld ki
    virtual ~Shape() {}
    /// tisztán virtuális = pure virtual
    virtual int nodeCount() const = 0;
};

class Square : public Shape {
public:
    /// final - utolsó override
    int nodeCount() const final { return 4; };
};

/** Nem lehetséges:
  * class SquareDerived : public Square {
  * public:
  *     int nodeCount() const override { return 10; }
  * };
  */

class Graph {
public:
    int nodeCount() const { return 42; };
};

class Mutant : public Square, public Graph {
public:
    /// kommenteld ki
    using Graph::nodeCount;
};

int main()
{
    Ember m;
    m.sayHi();
    printFajRossz(m);
    printFajJo(m);

    Eloleny* e = new Ember();

    delete e;

    // Nem egységbe zárt
    int x = 0, y = 0;
    x += 5;
    y += 5;

    /* Egységbe zárt
    Point p(0,0);
    p.eltol(5,5);
    */

    Shape* s = new Square();
    s->nodeCount(); // Square nodeCount
    delete s;

    Mutant t;
    cout << t.nodeCount() << endl;
    cout << t.Graph::nodeCount() << endl;
    cout << t.Square::nodeCount() << endl;
    // cout << t.Shape::nodeCount() << endl;
}