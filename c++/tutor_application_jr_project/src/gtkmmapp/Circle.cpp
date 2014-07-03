#include "Circle.h"

Circle::Circle(int type, double radius, double theta, double x_0, double y_0, double x, double y, double sides, double red, double green, double blue)
{
    this->type = type;
    this->radius = radius;
    this->x_0 = x_0;
    this->y_0 = y_0;
    this->sides = sides;
    this->theta = theta;
    this->x;
    this->y;
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Circle::~Circle()
{

}

double Circle::get_radius()
{
    return this->radius;
}

double Circle::get_x_0()
{
    return this->x_0;
}

double Circle::get_y_0()
{
    return this->y_0;
}

double Circle::get_sides()
{
    return this->sides;
}

int Circle::get_type()
{
    return this->type;
}

double Circle::get_theta()
{
    return this->theta;
}

double Circle::get_x()
{
    return this->x;
}

double Circle::get_y()
{
    return this->y;
}

double Circle::get_red()
{
	return this->red;
}

double Circle::get_green()
{
	return this->green;
}

double Circle::get_blue()
{
	return this->blue;
}
