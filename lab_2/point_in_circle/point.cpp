#include "point.hpp"

Point::Point() : m_x(0), m_y(0) {}
Point::Point(double x, double y) : m_x(x), m_y(y) {}

double Point::getX() const
{
    return m_x;
}

double Point::getY() const
{
    return m_y;
}

void Point::setX(double x)
{
    this->m_x = x;
}

void Point::setY(double y)
{
    this->m_y = y;
}

void Point::setXY(double x, double y)
{
    m_x = x;
    m_y = y;
}

void Point::write() const
{
    std::cout << "(" << m_x << "," << m_y << ")";
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.m_x << "," << p.m_y << ")";
    return os; /// Makes chaining operators possible.
}