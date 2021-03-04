#include "vec2d.hpp"
#include <cmath>

Vec2D::Vec2D() : m_x(0), m_y(0) {}

Vec2D::Vec2D(double x, double y) : m_x(x), m_y(y) {}

Vec2D Vec2D::operator+(const Vec2D& rhs) const
{
    return Vec2D(m_x + rhs.m_x, m_y + rhs.m_y);
}

Vec2D Vec2D::operator-(const Vec2D& rhs) const
{
    return Vec2D(m_x - rhs.m_x, m_y - rhs.m_y);
}

double Vec2D::operator*(const Vec2D& rhs) const
{
    return m_x * rhs.m_x + m_y * rhs.m_y;
}

bool Vec2D::isPerpendicular(const Vec2D& rhs) const
{
    return *this * rhs == 0;
}

double Vec2D::length() const
{
    return std::sqrt(*this * *this);
}

std::ostream& operator<<(std::ostream& os, const Vec2D& v)
{
    os << '<' << v.m_x << ", " << v.m_y << '>';
    return os;
}

std::istream& operator>>(std::istream& is, Vec2D& v)
{
    is >> v.m_x >> v.m_y;
    return is;
}