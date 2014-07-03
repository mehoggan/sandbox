/*
 * skybox.h
 *
 *  Created on: Sep 10, 2010
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
# include <GL/glut.h>  											// inclues gl.h, glu.h, ... others
# include <string>
# include <iostream>
# endif

using namespace std;

#ifndef EXPLOSION_H_
#define EXPLOSION_H_

class explosion
{
public:
	/*
	 * Constructors and De-constructor
	 */
	explosion();
	explosion(GLfloat x, GLfloat y, GLfloat z);
	~explosion();
	void draw(GLfloat radius1,GLfloat radius2,GLfloat radius3);
private:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat radius1;
	GLfloat diffuse1[4];
	GLfloat ambient1[4];
	GLfloat spectral1[4];
	GLfloat opacity1_d;
	GLfloat opacity1_a;
	GLfloat opacity1_s;
	GLfloat radisu2;
	GLfloat diffuse2[4];
	GLfloat ambient2[4];
	GLfloat spectral2[4];
	GLfloat opacity2_d;
	GLfloat opacity2_a;
	GLfloat opacity2_s;
	GLfloat radius3;
	GLfloat diffuse3[4];
	GLfloat ambient3[4];
	GLfloat spectral3[4];
	GLfloat opacity3_d;
	GLfloat opacity3_a;
	GLfloat opacity3_s;
	GLfloat time;
	GLfloat transMatrix[16];
};

#endif /* EXPLOSION_H_ */