/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2021. 03. 04.                  *
*   Project name: Most frequent element  *
*****************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include "stdlib.h"

// Exercise: Find the most frequent element of an array
// of integers with counting embedded in maximum search.

using namespace std;

vector<int> setup(string fileName)
{
    ifstream f(fileName.c_str());

    if (f.fail()) {
        cerr << "Invalid file name.\n";
        exit(1);
    }

    int e;
    vector<int> vec;
    while (f >> e) {
        vec.push_back(e);
    }

    return vec;
}

unsigned count(const vector<int>& vec, int num)
{
    unsigned counter = 0;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == num) {
            counter++;
        }
    }
    
    return counter;
}

int maxSearch(const vector<int>& vec)
{
    int maxElem = vec[0];
    unsigned maxCount = count(vec, vec[0]);

    for (unsigned int i = 1; i < vec.size(); i++) {
        unsigned currCount = count(vec, vec[i]);
        if (currCount > maxCount) {
            maxElem = vec[i];
            maxCount = currCount;
        }
    }

    return maxElem;
}

int main()
{
    int maxDepth, ind;
    vector<int> numbers = setup("input.txt");
    if (numbers.empty()) {
        cout << "Empty array provided. There is no most frequent element.\n";
    } else {
        cout << "Most frequent element of input array is " << maxSearch(numbers) << '\n';
    }
    
    return 0;
}
