#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.hpp"

class Circle {
public:
    Circle();
    Circle(const Point& center, double radius);
    Circle(double x, double y, double radius);
    /// Getter methods
    double getRadius() const;
    Point getCenter() const;
    /// Setter methods
    void setRadius(double radius);
    void setCenter(const Point& point);  /// Overloading
    void setCenter(double x, double y);
    /// Additional methods
    double area() const;
    double distance(const Point& point) const;
    bool contains(const Point& point) const;

private:
    Point m_center;
    double m_radius;
};

#endif
