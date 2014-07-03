#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

class Shape
{
public:
    Shape();
    virtual ~Shape() = 0;
    virtual double get_radius() = 0;
    virtual double get_x_0() = 0;
    virtual double get_y_0() = 0;
    virtual double get_sides() = 0;
    virtual int get_type() = 0;
    virtual double get_theta() = 0;
    virtual double get_x() = 0;
    virtual double get_y() = 0;
	virtual double get_red() = 0;
	virtual double get_green() = 0;
	virtual double get_blue() = 0;
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

#endif // SHAPE_H_INCLUDED
