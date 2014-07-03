/*
 * ship.h
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
#include <fstream>
# include <GL/glut.h>  											// glut.h includes gl.h and glu.h

# endif

# if defined (__Linux__)  										// Linux
# include <GL/glut.h>											// inclues gl.h, glu.h, ... others
# include <string>
# include <iostream>
# endif

using namespace std;

#ifndef TORPEDO_H_
#define TORPEDO_H_

class torus;

class torpedo
{
public:
	torpedo();
	torpedo(	double radius, double stacks, double slices, double red, double green, double blue,
				double x_o, double y_o, double z_o, double x_right, double y_right, double z_right,
				double x_up, double y_up, double z_up, double x_at, double y_at, double z_at, torus* target);
	~torpedo();
	/*
	 * Object specific functions
	 */
	void draw();
	void movement(GLfloat direction);
	void turn(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void seek_and_destroy();
	void Display_Matrix(char* operation, GLfloat matrix[16]);
	torus* get_Target();
	void set_Target();
	double get_Radius();
	GLfloat get_Rotate_Angle();
	GLfloat get_X_Right();
	void set_X_Right(GLfloat x_right);
	GLfloat get_Y_Right();
	void set_Y_Right(GLfloat y_right);
	GLfloat get_Z_Right();
	void set_Z_Right(GLfloat z_right);
	GLfloat get_X_Up();
	void set_X_Up(GLfloat x_up);
	GLfloat get_Y_Up();
	void set_Y_Up(GLfloat y_up);
	GLfloat get_Z_Up();
	void set_Z_Up(GLfloat z_up);
	GLfloat get_X_At();
	void set_X_At(GLfloat x_at);
	GLfloat get_Y_At();
	void set_Y_At(GLfloat y_at);
	GLfloat get_Z_At();
	void set_Z_At(GLfloat z_at);
	GLfloat get_X_Pos();
	void set_X_Pos(GLfloat x_pos);
	GLfloat get_Y_Pos();
	void set_Y_Pos(GLfloat y_pos);
	GLfloat get_Z_Pos();
	void set_Z_Pos(GLfloat z_pos);
	GLfloat get_X_Norm();
	GLfloat get_Y_Norm();
	GLfloat get_Z_Norm();
	int get_Angle_Direction();

private:
	double radius;
	double stacks;
	double slices;
	torus* target;
	GLfloat color[4];
	GLfloat Matrix[16];
	GLfloat rotateMatrix[16];
	GLfloat normalToTarget[3];
	GLfloat rotateAngle;
	int angleDirection;
	ofstream myfile;
	void cross_Product(GLfloat V[3], GLfloat U[3]);
	GLfloat dot_Product(GLfloat V[3], GLfloat U[3]);
};


#endif /* TORPEDO_H_ */
