#include "vec2d.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<Vec2D> setup()
{
    std::string filename;
    std::cout << "Filename:\n>>> ";
    std::cin >> filename;
    std::ifstream f(filename.c_str());

    if (f.fail()) {
        std::cerr << "Invalid filename!\n";
    }

    std::vector<Vec2D> vec;
    Vec2D vec2d;

    while (f >> vec2d) {
        vec.push_back(vec2d);
    }
    
    return vec;
}

bool arePerpendicular(const std::vector<Vec2D>& vec, const Vec2D& vec2d)
{
    Vec2D sum;
    for (const Vec2D& elem : vec) {
        sum = sum + elem;
    }

    return sum.isPerpendicular(vec2d);
}

int main()
{
    std::vector<Vec2D> vec = setup();

    Vec2D vec2d;
    std::cout << "Vector from console:\n>>> ";
    std::cin >> vec2d;

    std::string s = arePerpendicular(vec, vec2d) ? "" : "not ";
    std::cout << "The sum of the vectors of the input file are "
              << s << "perpendicular to the one read from console.\n";
}