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

#ifndef SKYBOX_H_
#define SKYBOX_H_

class skybox
{
public:
	/*
	 * Constructors and De-constructor
	 */
	skybox();
	skybox(int size_of_box);
	~skybox();
	void draw();
	
private:
	GLuint texture;
	float size;
	unsigned char* data1;
	unsigned char* data2;
	unsigned char* data3;
	unsigned char* data4;
	unsigned char* data5;
	unsigned char* data6;
	FILE* file1;
	FILE* file2;
	FILE* file3;
	FILE* file4;
	FILE* file5;
	FILE* file6;
};

#endif /* TORUS_H_ */