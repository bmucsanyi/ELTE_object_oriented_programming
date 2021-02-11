/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2021. 02. 11.                  *
*   Project name: Highest valley         *
*****************************************/

/// Settings -> Editor -> SpellChecker -> Uncheck checkboxes
/// Settings -> Compiler -> Have g++ follow the C++11 ISO C++ language standard

#include <iostream>
#include <vector>
#include <fstream>
#include "stdlib.h"

/// Numbers for the 1st assignment will be handed out in the upcoming days
/// Homework: Finding the most frequent element of an array
///           of integers with counting embedded in maximum search.
/// Please remove the bin and obj folders when uploading your work to TMS.

/// We introduce all the functions, classes and constants
/// from the std (standard) namespace to our main namespace.
using namespace std;

vector<int> setup(string fileName)
{
    /// We create an input file stream (ifstream),
    /// and we provide its constructor the name of the file
    /// we want to read from.
    ifstream f(fileName.c_str());
    // We will need the c_str() function at the atoi() function from C, too.

    /// f.fail(): For some reason we are unable to open the provided file.
    /// Reasons can be: Insufficient permission for the file,
    /// or the file doesn't exist.
    if (f.fail()) {
        cerr << "Invalid file name.\n"; // #include <iostream> is needed
        exit(1); // #include "stdlib.h" is needed
    }

    int e;
    /// We instantiate std::vector.
    /// Some of you might have seen this type in previous introductionary
    /// courses (most of you have only used arrays), now we will learn to
    /// use them in-depth.
    /// The std::vector is a dynamic array, i.e. it can be resized in its
    /// lifetime.
    /// This is a template class (interested students should look it up),
    /// so we provide the template parameters between the '<>' characters.
    /// Template parameters in the case of std::vector show what elements
    /// the vector contains.
    vector<int> vec; // #include <vector>
    while (f >> e) {
        /// push_back is a method of std::vector, that allows us to push an
        //// element to the end of our std::vector object.
        vec.push_back(e);
        cout << e << " ";
    }

    cout << endl << endl;
    return vec;
}

/// If a function takes a parameter by reference (&),
/// then inside the function we refer to exactly the same variable
/// we provided to the function when calling it.
/// Thus, the assigned value of the variable can also be changed.
/// (It is basically equivalent to using pointers, but we don't have
/// to suffer with derefering.)
/// As the compiler doesn't have to copy the variable, it is sometimes
/// also remarkably more efficient to use references.
/// However, if we don't change the value of a parameter and it is
/// pass-by-reference, we can use the const keyword to prohibit modification
/// inside the function.
bool condMaxSearch(const vector<int>& vec, int& maxDepth, int& ind)
{
    bool l = false;
    for (int i = 1; i < int(vec.size() - 1); i++) {
        if (l && vec[i+1] > vec[i] && vec[i-1] > vec[i]) {
            if (maxDepth < vec[i]) {
                maxDepth = vec[i];
                ind = i;
            }
        }
        else if (!l && vec[i+1] > vec[i] && vec[i-1] > vec[i]) {
            l = true;
            maxDepth = vec[i];
            ind = i;
        }
        /// Totally unnecessary (and ugly):
        // else {
        //     continue;
        // }
    }
    /// Another ugly snippet:
    // if (l) return true;
    // else return false;
    /// Instead:
    return l;
}

int main()
{
    int maxDepth, ind;
    vector<int> heights = setup("input3.txt");
    if (condMaxSearch(heights, maxDepth, ind)) {
        cout << "Maximum depth: " << maxDepth << " Index: " << ind + 1 << "." << endl;
    }
    else {
        cout << "There are no valleys.\n";
    }
    return 0;
}
