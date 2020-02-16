#include "circle.h"
#include <math.h>
#include <stdlib.h>

const double PI = 3.141592653589793238463;

Circle::Circle() : center(), radius(0) {}

Circle::Circle(Point center, double radius) {
    if (radius < 0) { std::cout << "Invalid radius!\n"; exit(1); }

    this->center = center;
    this->radius = radius;
}

Circle::Circle(double x, double y, double radius) {
    if (radius < 0) { std::cout << "Invalid radius!\n"; exit(1); }

    center.setX(x);
    center.setY(y);
    this->radius = radius;
}

double Circle::getRadius() const {
    return radius;
}

Point Circle::getCenter() const {
    return center;
}

void Circle::setRadius(double radius) {
    if(radius < 0) {std::cout << "Invalid radius!\n"; exit(1);}
    this->radius = radius;
}

void Circle::setCenter(Point center) {
    this->center = center;
}

void Circle::setCenter(double x, double y) {
    center.setX(x);
    center.setY(y);
}

double Circle::area() const {
    return radius * radius * PI;
}

double Circle::distance(Point point) const {
    return sqrt(pow((point.getX() - center.getX()), 2) + pow((point.getY() - center.getY()), 2));
}

bool Circle::contains(Point point) const {
    return distance(point) <= radius;
}
