#include "circle.hpp"
#include <math.h>
#include <stdlib.h>

const double PI = 3.141592653589793238463;

Circle::Circle() : m_center(), m_radius(0) {}

Circle::Circle(const Point& center, double radius)
{
    if (radius < 0) { std::cout << "Invalid radius!\n"; exit(1); }

    m_center = center;
    m_radius = radius;
}

Circle::Circle(double x, double y, double radius)
{
    if (radius < 0) { std::cout << "Invalid radius!\n"; exit(1); }

    m_center.setX(x);
    m_center.setY(y);
    m_radius = radius;
}

double Circle::getRadius() const
{
    return m_radius;
}

Point Circle::getCenter() const
{
    return m_center;
}

void Circle::setRadius(double radius)
{
    if(radius < 0) {std::cout << "Invalid radius!\n"; exit(1);}
    m_radius = radius;
}

void Circle::setCenter(const Point& center)
{
    m_center = center;
}

void Circle::setCenter(double x, double y)
{
    m_center.setX(x);
    m_center.setY(y);
}

double Circle::area() const
{
    return m_radius * m_radius * PI;
}

double Circle::distance(const Point& point) const
{
    return sqrt(pow((point.getX() - m_center.getX()), 2) + pow((point.getY() - m_center.getY()), 2));
}

bool Circle::contains(const Point& point) const
{
    return distance(point) <= m_radius;
}
