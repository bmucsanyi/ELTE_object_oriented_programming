#ifndef PONT_H
#define PONT_H

#include <iostream>

class Point {
public:
    /// Constructors
    /// The constructor is called each time we create an object of type Point.
    /// We don't have to write an explicit destructor,
    /// as we haven't allocated memory dynamically.
    Point(); 
    Point(double x, double y);
    /// Getter methods
    double getX() const; // Const keyword for querys.
    double getY() const; // Const keyword for querys..
    /// Setter methods
    void setX(double x);
    void setY(double y);
    void setXY(double x, double y);
    /// Additional methods
    void write() const;
    friend std::ostream& operator<<(std::ostream& os, const Point& p);

private:
    double m_x, m_y;
};

#endif
