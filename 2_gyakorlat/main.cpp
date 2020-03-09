/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2020. 02. 16.                  *
*   Project name: Points and Circles     *
*****************************************/

#include <iostream>
#include "point.h"
#include "circle.h"
#include <fstream>
#include <vector>
#include <stdlib.h>

/// A táblás gyakorlaton megadtátok a
/// kör és pont típusokat, illetve
/// megkerestétek az első olyan pontot adott pontok közül,
/// amelyik a megadott körön belül helyezkedik el.
/// Most ezeket az osztályokat implementáljuk C++-ban.

/// Ha terminálból dolgoztok:
/// g++ -ansi -pedantic -W -Wall -std=c++11  main.cpp point.cpp circle.cpp -o main.out

/// Szorgalmi feladat: A gyakorlathoz hasonló módon
/// a komplex számok típusának megadása.
/// Canvas-ben lehet beadni a szorgalmikat.

using namespace std;

vector<Point> setup();
Circle readCircle();
int count(const vector<Point>& v, const Circle& k);

int main()
{
    /// A Point class tesztelése
    /*Point p;
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
    cout << p.getX();*/
    vector<Point> v = setup();
    Circle k = readCircle();
    int pointCount = count(v, k);

    cout << "The circle contains "
         << pointCount
         << (pointCount != 1 ? " points.\n" : " point.\n");

    return 0;
}

vector<Point> setup()
{
    string fileName;
    cout << "Filename:\n>>>";
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
    cout << "Coordinates of the circle's center:\n>>>";
    cin >> x;
    cout << ">>>";
    cin >> y;
    cout << "Radius of the circle:\n>>>";
    cin >> r;

    return Circle(x, y, r);
}

int count(const vector<Point>& v, const Circle& k)
{
    int c = 0;
    for(Point p : v) {
        if (k.contains(p)) c++;
    }

    return c;
}
