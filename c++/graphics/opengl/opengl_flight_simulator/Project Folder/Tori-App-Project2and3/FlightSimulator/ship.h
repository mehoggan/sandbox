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
# include <GL/glut.h>  											// glut.h includes gl.h and glu.h

# endif

# if defined (__Linux__)  										// Linux
# include <GL/glut.h>											// inclues gl.h, glu.h, ... others
# include <string>
# include <iostream>
# endif

using namespace std;
class torus;

#ifndef SHIP_H_
#define SHIP_H_

class ship
{
public:
	ship();
	ship(	double radius, double height, double stacks, double slices, double red, double green, double blue,
			double x_o, double y_o, double z_o, double pitch, double turn, double roll);
	~ship();
	/*
	 * Object specific functions
	 */
	void draw();
	void movement(GLfloat direction);
	void turn(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void orient_ship(torus* curr_torus);
	void Display_Matrix(char* operation, GLfloat matrix[16]);
	double getRadius();
	double getHeight();
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
	void drawTriModel(int listId, float scale);

private:
	double radius;
	double height;
	double stacks;
	double slices;
	GLfloat color[4];
	GLfloat Matrix[16];
	GLfloat rotateMatrix[16];
};


#endif /* SHIP_H_ */
