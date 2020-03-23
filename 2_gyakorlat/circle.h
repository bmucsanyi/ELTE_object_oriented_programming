#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"

class Circle {
public:
    Circle();
    Circle(Point center, double radius);
    Circle(double x, double y, double radius);
    /// Getter metódusok
    double getRadius() const;
    Point getCenter() const;
    /// Setter metódusok
    void setRadius(double radius);
    void setCenter(Point point); /// Túlterhelés
    void setCenter(double x, double y);
    /// Egyéb metódusok
    double area() const;
    double distance(Point point) const;
    bool contains(Point point) const;

private:
    Point center_;
    double radius_;
};

#endif
