#ifndef VEC2D_H
#define VEC2D_H

#include <iostream>

class Vec2D {
public:
    Vec2D();
    Vec2D(double x, double y);

    Vec2D operator+(const Vec2D& rhs) const;
    Vec2D operator-(const Vec2D& rhs) const;
    double operator*(const Vec2D& rhs) const;

    bool isPerpendicular(const Vec2D& rhs) const;
    double length() const;

    friend std::ostream& operator<<(std::ostream& os, const Vec2D& v);
    friend std::istream& operator>>(std::istream& is, Vec2D& v);
private:
    double m_x, m_y;
};

#endif