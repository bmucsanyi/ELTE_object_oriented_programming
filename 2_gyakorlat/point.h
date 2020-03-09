#ifndef PONT_H
#define PONT_H

#include <iostream>

class Point
{
    public:
        /// Konstruktorok
        /// A konstruktor mindig lefut, amikor létrehozunk egy Point típusú változót.
        /// Destruktort expliciten most nem írunk, mert nem foglaltunk le dinamikusan memóriaterületet.
        Point(); 
        Point(double x, double y);
        /// Getter metódusok
        double getX() const; // Const kulcsszó a querykhez.
        double getY() const; // Const kulcsszó a querykhez.
        /// Setter metódusok
        void setX(double x);
        void setY(double y);
        void setXY(double x, double y);
        /// Egyéb metódusok
        void write() const;
        friend std::ostream& operator<<(std::ostream& os, const Point& p);

    private:
        double x,y;
};

#endif
