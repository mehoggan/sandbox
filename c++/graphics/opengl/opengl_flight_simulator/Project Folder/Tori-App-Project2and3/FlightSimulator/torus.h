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
# include <GL/glut.h>  											// glut.h includes gl.h and glu.h

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
	torus(	double inner_radius, double outer_radius, double nsides, double rings, double red, double green, double blue,
			double x_o, double y_o, double z_o	);
	~torus();
	
	void draw(char* torus_name);
	void drawTriEarth(int listId, float scale);
	void drawTriGolfBall(int listId, float scale);
	void drawTriJupiter(int listId, float scale);
	void drawTriMars(int listId, float scale);
	void rotate(GLfloat rotate);
	void Display_Matrix(char* operation, GLfloat matrix[16]);
	double get_Inner_Radius();
	double get_Outer_Radius();
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
private:
	double inner_radius;
	double outer_radius;
	double nsides;
	double rings;
	double radial_distance;
	double angular_position;
	GLfloat color[4];
	GLfloat Matrix[16];
	GLfloat rotateMatrix[16];
};

#endif /* TORUS_H_ */
