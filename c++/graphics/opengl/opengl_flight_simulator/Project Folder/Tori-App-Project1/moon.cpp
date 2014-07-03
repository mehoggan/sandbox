/*
 * moon.cpp
 *
 *  Created on: Sep 16, 2010
 *      Author: Matthew Hoggan
 */

#include "moon.h"

moon::moon()
{

}

moon::moon(	double radius, double stacks, double slices,
			double x_coord, double y_coord, double z_coord, double angle,
			double x_axis, double y_axis, double z_axis, double red, double green, double blue	)
{
	this->radius = radius;
	this->stacks = stacks;
	this->slices = slices;
	this->x_coord = x_coord;
	this->y_coord = y_coord;
	this->z_coord = z_coord;
	this->angle_rotate = angle;
	this->x_vector = x_axis;
	this->y_vector = y_axis;
	this->z_vector = z_axis;
	this->color[0] = red;
	this->color[1] = green;
	this->color[2] = blue;
}

moon::~moon()
{
}

/*
 * Object specific functions
 */
void moon::draw()
{
	glPushMatrix();
		glTranslatef(this->x_coord, this->y_coord, this->z_coord);
		glRotatef(this->angle_rotate, this->x_vector, this->y_vector, this->z_vector);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, this->color);
		glutSolidSphere(this->radius, this->stacks, this->slices);
	glPopMatrix();
}

void moon::turn()
{
}

void moon::move()
{
}
/*
 * Get functions
 */
double moon::get_radius()
{
	return this->radius;
}

double moon::get_stacks()
{
	return this->stacks;
}

double moon::get_slices()
{
	return this->slices;
}

double moon::get_x_coord()
{
	return this->x_coord;
}

double moon::get_y_coord()
{
	return this->y_coord;
}

double moon::get_z_coord()
{
	return this->z_coord;
}

double moon::get_angle_rotate()
{
	return this->angle_rotate;
}

double moon::get_x_vector()
{
	return this->x_vector;
}

double moon::get_y_vector()
{
	return this->y_vector;
}

double moon::get_z_vector()
{
	return this->z_vector;
}

double moon::get_red()
{
	return this->color[0];
}

double moon::get_green()
{
	return this->color[1];
}

double moon::get_blue()
{
	return this->color[2];
}
/*
 * Set functions
 */
void moon::set_radius(double radius)
{
	this->radius = radius;
}

void moon::set_stacks(double stacks)
{
	this->stacks = stacks;
}

void moon::set_slices(double slices)
{
	this->slices = slices;
}

void moon::set_x_coord(double x_coord)
{
	this->x_coord = x_coord;
}

void moon::set_y_coord(double y_coord)
{
	this->y_coord = y_coord;
}

void moon::set_z_coord(double z_coord)
{
	this->z_coord = z_coord;
}

void moon::set_angle_rotate(double angle_rotate)
{
	this->angle_rotate = angle_rotate;
}

void moon::set_x_vector(double x_vector)
{
	this->x_vector = x_vector;
}

void moon::set_y_vector(double y_vector)
{
	this->y_vector = y_vector;
}

void moon::set_z_vector(double z_vector)
{
	this->z_vector = z_vector;
}

void moon::set_red(double red)
{
	this->color[0] = red;
}

void moon::set_green(double green)
{
	this->color[1] = green;
}

void moon::set_blue(double blue)
{
	this->color[2] = blue;
}

