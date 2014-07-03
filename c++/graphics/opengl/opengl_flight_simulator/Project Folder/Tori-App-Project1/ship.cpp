/*
 * ship.cpp
 *
 *  Created on: Sep 16, 2010
 *      Author: Matthew Hoggan
 */

#include "ship.h"

ship::ship()
{

}

ship::ship(	double radius, double height, double stacks, double slices,
			double x_coord, double y_coord, double z_coord, double angle,
			double x_axis, double y_axis, double z_axis, double red, double green, double blue	)
{
	this->radius = radius;
	this->height = height;
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

ship::~ship()
{
}

/*
 * Object specific functions
 */
void ship::draw()
{
	glPushMatrix();
		glTranslatef(this->x_coord, this->y_coord, this->z_coord);
		glRotatef(this->angle_rotate, this->x_vector, this->y_vector, this->z_vector);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, this->color);
		glutSolidCone(this->radius, this->height, this->stacks, this->slices);
	glPopMatrix();
}

void ship::turn()
{
}

void ship::move()
{
}

/*
 * Get functions
 */
double ship::get_radius()
{
	return this->radius;
}

double ship::get_height()
{
	return this->height;
}

double ship::get_stacks()
{
	return this->stacks;
}

double ship::get_slices()
{
	return this->slices;
}

double ship::get_x_coord()
{
	return this->x_coord;
}

double ship::get_y_coord()
{
	return this->y_coord;
}

double ship::get_z_coord()
{
	return this->z_coord;
}

double ship::get_angle_rotate()
{
	return this->angle_rotate;
}

double ship::get_x_vector()
{
	return this->x_vector;
}

double ship::get_y_vector()
{
	return this->y_vector;
}

double ship::get_z_vector()
{
	return this->z_vector;
}

double ship::get_red()
{
	return this->color[0];
}

double ship::get_green()
{
	return this->color[1];
}

double ship::get_blue()
{
	return this->color[2];
}
/*
 * Set functions
 */
void ship::set_radius(double radius)
{
	this->radius = radius;
}

void ship::set_height(double height)
{
	this->height = height;
}

void ship::set_stacks(double stacks)
{
	this->stacks = stacks;
}

void ship::set_slices(double slices)
{
	this->slices = slices;
}

void ship::set_x_coord(double x_coord)
{
	this->x_coord = x_coord;
}

void ship::set_y_coord(double y_coord)
{
	this->y_coord = y_coord;
}

void ship::set_z_coord(double z_coord)
{
	this->z_coord = z_coord;
}

void ship::set_angle_rotate(double angle_rotate)
{
	this->angle_rotate = angle_rotate;
}

void ship::set_x_vector(double x_vector)
{
	this->x_vector = x_vector;
}

void ship::set_y_vector(double y_vector)
{
	this->y_vector = y_vector;
}

void ship::set_z_vector(double z_vector)
{
	this->z_vector = z_vector;
}

void ship::set_red(double red)
{
	this->color[0] = red;
}

void ship::set_green(double green)
{
	this->color[1] = green;
}

void ship::set_blue(double blue)
{
	this->color[2] = blue;
}
