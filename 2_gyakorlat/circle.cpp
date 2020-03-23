#include "circle.h"
#include <math.h>
#include <stdlib.h>

const double PI = 3.141592653589793238463;

Circle::Circle() : center_(), radius_(0) {}

Circle::Circle(Point center, double radius)
{
    if (radius < 0) { std::cout << "Invalid radius!\n"; exit(1); }

    center_ = center;
    radius_ = radius;
}

Circle::Circle(double x, double y, double radius)
{
    if (radius < 0) { std::cout << "Invalid radius!\n"; exit(1); }

    center_.setX(x);
    center_.setY(y);
    radius_ = radius;
}

double Circle::getRadius() const
{
    return radius_;
}

Point Circle::getCenter() const
{
    return center_;
}

void Circle::setRadius(double radius)
{
    if(radius < 0) {std::cout << "Invalid radius!\n"; exit(1);}
    radius_ = radius;
}

void Circle::setCenter(Point center)
{
    center_ = center;
}

void Circle::setCenter(double x, double y)
{
    center_.setX(x);
    center_.setY(y);
}

double Circle::area() const
{
    return radius_ * radius_ * PI;
}

double Circle::distance(Point point) const
{
    return sqrt(pow((point.getX() - center_.getX()), 2) + pow((point.getY() - center_.getY()), 2));
}

bool Circle::contains(Point point) const
{
    return distance(point) <= radius_;
}
