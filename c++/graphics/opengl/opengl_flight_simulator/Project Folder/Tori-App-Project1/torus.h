/*
 * torus.h
 *
 *  Created on: Sep 16, 2010
 *      Author: Matthew Hoggan
 */

# define __Windows__
//# define __Linux__

# if defined (__Windows__)
# include <windows.h>
# include <string>
# include <iostream>
# include <glut.h>  											// glut.h includes gl.h and glu.h

# endif

# if defined (__Linux__)  										// Linux
# include <GL/glut.h>											// inclues gl.h, glu.h, ... others
# include <string>
# include <iostream>
# endif

using namespace std;

#ifndef TORUS_H_
#define TORUS_H_

class torus
{
public:
	/*
	 * Constructors and De-constructor
	 */
	torus();
	torus(	double inner_radius, double outer_radius, double nsides, double rings,
			double x_coord, double y_coord, double z_coord, double angle,
			double x_axis, double y_axis, double z_axis, double red, double green, double blue	);
	~torus();
	/*
	 * Object specific functions
	 */
	void draw();
	void turn();
	void move();
	/*
	 * Get functions
	 */
	double get_inner_radius();
	double get_outer_radius();
	double get_nsides();
	double get_rings();
	double get_x_coord();
	double get_y_coord();
	double get_z_coord();
	double get_angle_rotate();
	double get_x_vector();
	double get_y_vector();
	double get_z_vector();
	double get_red();
	double get_green();
	double get_blue();
	/*
	 * Set functions
	 */
	void set_inner_radius(double inner_radius);
	void set_outer_radius(double outer_radius);
	void set_nsides(double nsides);
	void set_rings(double rings);
	void set_x_coord(double x_coord);
	void set_y_coord(double y_coord);
	void set_z_coord(double z_coord);
	void set_angle_rotate(double angle_rotate);
	void set_x_vector(double x_vector);
	void set_y_vector(double y_vector);
	void set_z_vector(double z_vector);
	void set_red(double red);
	void set_green(double green);
	void set_blue(double blue);
private:
	double inner_radius;
	double outer_radius;
	double nsides;
	double rings;
	double x_coord;
	double y_coord;
	double z_coord;
	double angle_rotate;
	double x_vector;
	double y_vector;
	double z_vector;
	GLfloat color[4];
};

#endif /* TORUS_H_ */
