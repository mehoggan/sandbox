#include "Polygon.h"

Polygon::Polygon(int type, double radius, double theta, double x_0, double y_0, double x, double y, double sides, double red, double green, double blue)
{
    this->type = type;
    this->radius = radius;
    this->x_0 = x_0;
    this->y_0 = y_0;
    this->sides = sides;
    this->theta = theta;
    this->x = x;
    this->y = y;
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Polygon::~Polygon()
{

}

double Polygon::get_radius()
{
    return this->radius;
}

double Polygon::get_x_0()
{
    return this->x_0;
}

double Polygon::get_y_0()
{
    return this->y_0;
}

double Polygon::get_sides()
{
    return this->sides;
}

int Polygon::get_type()
{
    return this->type;
}

double Polygon::get_theta()
{
    return this->theta;
}

double Polygon::get_x()
{
    return this->x;
}

double Polygon::get_y()
{
    return this->y;
}

double Polygon::get_red()
{
	return this->red;
}

double Polygon::get_green()
{
	return this->green;
}

double Polygon::get_blue()
{
	return this->blue;
}
