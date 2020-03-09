#include "point.h"

Point::Point() : x(0), y(0) {}
Point::Point(double x, double y) : x(x), y(y) {}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

void Point::setX(double x)
{
    this->x = x;
}

void Point::setY(double y)
{
    this->y = y;
}

void Point::setXY(double x, double y)
{
    this->x = x;
    this->y = y;
}

void Point::write() const
{
    std::cout << "(" << x << "," << y << ")";
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os; /// Lehetővé tesszük a kiírások láncolását.
}