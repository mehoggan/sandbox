#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include "Shape.h"

class Polygon : public Shape
{
public:
    Polygon(int type, double radius, double theta, double x_0, double y_0, double x, double y, double sides, double red, double green, double blue);
    ~Polygon();
    double get_x_0();
    double get_y_0();
    double get_radius();
    double get_sides();
    int get_type();
    double get_theta();
    double get_x();
    double get_y();
	double get_red();
	double get_green();
	double get_blue();
private:
    double x_0;
    double y_0;
    double x;
    double y;
    double radius;
    double sides;
    int type;
    double theta;
	double red;
	double green;
	double blue;
};


#endif // POLYGON_H_INCLUDED
