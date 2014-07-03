#include "Square.h"

Square::Square(int type, double radius, double theta, double x_0, double y_0, double x, double y, double sides, double red, double green, double blue)
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

Square::~Square()
{

}

double Square::get_radius()
{
    return this->radius;
}

double Square::get_x_0()
{
    return this->x_0;
}

double Square::get_y_0()
{
    return this->y_0;
}

double Square::get_sides()
{
    return this->sides;
}

int Square::get_type()
{
    return this->type;
}

double Square::get_theta()
{
    return this->theta;
}

double Square::get_x()
{
    return this->x;
}

double Square::get_y()
{
    return this->y;
}

double Square::get_red()
{
	return this->red;
}

double Square::get_green()
{
	return this->green;
}

double Square::get_blue()
{
	return this->blue;
}
