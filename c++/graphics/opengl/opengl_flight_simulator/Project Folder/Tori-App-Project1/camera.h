/*
 * camera.h
 *
 *  Created on: Sep 21, 2010
 *      Author: Matthew
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

#ifndef CAMERA_H_
#define CAMERA_H_

class camera
{
public:
	camera();
	~camera();
	void perspective(double angle, double aspect, double near, double far);
	void lookat(double eye_X, double eye_Y, double eye_Z, double at_X, double at_Y, double at_Z,
				double vector_X, double vector_Y, double vector_Z);
	double get_angle();
	double get_aspect();
	double get_near_plane();
	double get_far_plane();
	double get_eye_X();
	double get_eye_Y();
	double get_eye_Z();
	double get_at_X();
	double get_at_Y();
	double get_at_Z();
	double get_vector_X();
	double get_vector_Y();
	double get_vector_Z();
	void set_angle(double angle);
	void set_aspect(double aspect);
	void set_near_plane(double near);
	void set_far_plane(double far);
	void set_eye_X(double eye_X);
	void set_eye_Y(double eye_Y);
	void set_eye_Z(double eye_Z);
	void set_at_X(double at_X);
	void set_at_Y(double at_Y);
	void set_at_Z(double at_Z);
	void set_vector_X(double vector_X);
	void set_vector_Y(double vector_Y);
	void set_vector_Z(double vector_Z);
private:
	double angle;
	double aspect;
	double near_plane;
	double far_plane;
	double eye_X;
	double eye_Y;
	double eye_Z;
	double at_X;
	double at_Y;
	double at_Z;
	double vector_X;
	double vector_Y;
	double vector_Z;
};

#endif /* CAMERA_H_ */
