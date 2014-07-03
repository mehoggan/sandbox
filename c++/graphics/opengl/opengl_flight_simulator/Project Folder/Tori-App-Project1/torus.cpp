/*
 * torus.cpp
 *
 *  Created on: Sep 16, 2010
 *      Author: Matthew Hoggan
 */

#include "torus.h"

/*
 * Constructors and De-constructors
 */
torus::torus()
{

}

torus::torus(	double inner_radius, double outer_radius, double nsides, double rings,
				double x_coord, double y_coord, double z_coord, double angle,
				double x_axis, double y_axis, double z_axis, double red, double green, double blue)
{
	this->inner_radius = inner_radius;
	this->outer_radius = outer_radius;
	this->nsides = nsides;
	this->rings = rings;
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
	this->color[3] = 1.0;
}

torus::~torus()
{
}
/*
 * Draw functions
 */
void torus::draw()
{
	glPushMatrix();
		glTranslatef(this->x_coord, this->y_coord, this->z_coord);
		glRotatef(this->angle_rotate, this->x_vector, this->y_vector, this->z_vector);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, this->color);
		glutSolidTorus(this->inner_radius, this->outer_radius, this->nsides, this->rings);
	glPopMatrix();
}

void torus::turn()
{
}

void torus::move()
{
}

/*
* Get functions
*/
double torus::get_inner_radius()
{
	return this->inner_radius;
}

double torus::get_outer_radius()
{
	return this->outer_radius;
}

double torus::get_nsides()
{
	return this->nsides;
}

double torus::get_rings()
{
	return this->rings;
}

double torus::get_x_coord()
{
	return this->x_coord;
}

double torus::get_y_coord()
{
	return this->y_coord;
}

double torus::get_z_coord()
{
	return this->z_coord;
}

double torus::get_angle_rotate()
{
	return this->angle_rotate;
}

double torus::get_x_vector()
{
	return this->x_vector;
}

double torus::get_y_vector()
{
	return this->y_vector;
}

double torus::get_z_vector()
{
	return this->z_vector;
}

double torus::get_red()
{
	return this->color[0];
}

double torus::get_green()
{
	return this->color[1];
}

double torus::get_blue()
{
	return this->color[2];
}

/*
 * Set functions
 */
void torus::set_inner_radius(double inner_radius)
{
	this->inner_radius = inner_radius;
}

void torus::set_outer_radius(double outer_radius)
{
	this->outer_radius = outer_radius;
}

void torus::set_nsides(double nsides)
{
	this->nsides = nsides;
}

void torus::set_rings(double rings)
{
	this->rings = rings;
}

void torus::set_x_coord(double x_coord)
{
	this->x_coord = x_coord;
}

void torus::set_y_coord(double y_coord)
{
	this->y_coord = y_coord;
}

void torus::set_z_coord(double z_coord)
{
	this->z_coord = z_coord;
}

void torus::set_angle_rotate(double angle_rotate)
{
	this->angle_rotate = angle_rotate;
}

void torus::set_x_vector(double x_vector)
{
	this->x_vector = x_vector;
}

void torus::set_y_vector(double y_vector)
{
	this ->y_vector = y_vector;
}

void torus::set_z_vector(double z_vector)
{
	this->z_vector = z_vector;
}

void torus::set_red(double red)
{
	this->color[0] = red;
}

void torus::set_green(double green)
{
	this->color[1] = green;
}

void torus::set_blue(double blue)
{
	this->color[2] = blue;
}

