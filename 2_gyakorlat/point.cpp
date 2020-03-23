#include "point.h"

Point::Point() : x_(0), y_(0) {}
Point::Point(double x, double y) : x_(x), y_(y) {}

double Point::getX() const
{
    return x_;
}

double Point::getY() const
{
    return y_;
}

void Point::setX(double x)
{
    this->x_ = x;
}

void Point::setY(double y)
{
    this->y_ = y;
}

void Point::setXY(double x, double y)
{
    x_ = x;
    y_ = y;
}

void Point::write() const
{
    std::cout << "(" << x_ << "," << y_ << ")";
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.x_ << "," << p.y_ << ")";
    return os; /// Lehetővé tesszük a kiírások láncolását.
}