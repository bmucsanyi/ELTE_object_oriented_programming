#include <iostream>
#include "matrix.hpp"

using namespace std;

int main()
{
    matrix a;
    matrix b;
    matrix c(2);
    cout << "a:\n" << a << endl << endl;
    cout << "b:\n" << b << endl;
    cout << "a[2,3]= " << a.getElement(2,3) << endl;
    cout << "a[3,2]= " << a.getElement(3,2) << endl << endl;
    cout << "a+b:\n" << matrix::add(a,b) << endl << endl;
    cout << "a*b:\n" << matrix::multiply(a,b) << endl << endl;
    cout << "invalid sum:\n" << matrix::add(c,a) << endl << endl;
    cout << "invalid mul:\n" << matrix::multiply(c,b) << endl << endl;
    a.setVec({2,3,4,5});
    cout << "invalid vector length:\n" << a << endl << endl;
    return 0;
}
