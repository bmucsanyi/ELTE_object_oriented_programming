/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2020. 02. 16.                  *
*   Project name: Points and Circles     *
*****************************************/

#include <iostream>
#include "point.hpp"
#include "circle.hpp"
#include <fstream>
#include <vector>
#include <stdlib.h>

/// On the practice you've designed the point and
/// circle types, and searched for a point which
/// is inside the specified circle.
/// Now we'll implement these classes in C++.

/// If you work from the terminal (like me):
/// g++ -ansi -pedantic -Wall -Wextra -std=c++11  main.cpp point.cpp circle.cpp -o main.out
/// g++ -ansi -pedantic -Wall -Wextra -std=c++1 *.cpp -o main.out

/// Homework: In the same way as on this lab,
/// implement the type of complex numbers,
/// with addition, subtraction, multiplication and length.
/// Homeworks are to be submitted on Canvas.

using namespace std;

/// Forward declaration of functions
vector<Point> setup();
Circle readCircle();
bool search(const vector<Point>& v, const Circle& c, unsigned int& ind);

int main()
{
    /// Testing of the Point class
    /* Point p;
    p.write();
    cout << p;
    Point p2(-3, 2.4);
    cout << p2;
    p.setX(3);
    cout << p;
    p.setY(4);
    cout << p;
    p.setXY(5,6);
    cout << p;
    cout << p.getX(); */

    /// The specified exercise
    vector<Point> v = setup();
    Circle c = readCircle();

    unsigned int ind;
    if (search(v, c, ind)) {
        cout << "The circle contains "
             << v[ind]
             << ".\n";
    } else {
        cout << "None of the points are in the circle.\n";
    }

    return 0;
}

vector<Point> setup()
{
    string fileName;
    cout << "Filename:\n>>> ";
    cin >> fileName;

    ifstream f(fileName.c_str());
    if (f.fail()) {
        cerr << "Invalid filename!\n";
        exit(1);
    }

    double x, y;
    vector<Point> vec;
    while (f >> x >> y) {
        Point z(x, y);
        vec.push_back(z);
    }
    cout << endl;

    return vec;
}

Circle readCircle()
{
    double x, y, r;
    cout << "Coordinates of the circle's center:\n>>> ";
    cin >> x;
    cout << ">>> ";
    cin >> y;
    cout << "Radius of the circle:\n>>> ";
    cin >> r;

    return Circle(x, y, r);
}

bool search(const vector<Point>& v, const Circle& c, unsigned int& ind)
{
    bool l = false;
    for (unsigned int i = 0; i < v.size() && !l; ++i) {
        l = c.contains(v[i]);
        ind = i;
    }
    return l;

    /// An easier approach:
    /*
    for (const Point& p : v) {
        if (c.contains(p)) return true;
    }
    return false;
    */
}