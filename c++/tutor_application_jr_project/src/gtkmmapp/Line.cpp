#include "Line.h"

Line::Line(int type, double radius, double theta, double x_0, double y_0, double x, double y, double sides, double red, double green, double blue)
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

Line::~Line()
{

}

double Line::get_radius()
{
    return this->radius;
}

double Line::get_x_0()
{
    return this->x_0;
}

double Line::get_y_0()
{
    return this->y_0;
}

double Line::get_sides()
{
    return this->sides;
}

int Line::get_type()
{
    return this->type;
}

double Line::get_theta()
{
    return this->theta;
}

double Line::get_x()
{
    return this->x;
}

double Line::get_y()
{
    return this->y;
}

double Line::get_red()
{
	return this->red;
}

double Line::get_green()
{
	return this->green;
}

double Line::get_blue()
{
	return this->blue;
}
