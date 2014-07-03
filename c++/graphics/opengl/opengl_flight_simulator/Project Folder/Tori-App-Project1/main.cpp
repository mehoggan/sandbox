/*
 * main.cpp
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
# include <glut.h>  											// glut.h includes gl.h and glu.h
# endif

# if defined (__Linux__)  										// Linux
# include <GL/glut.h>  											// inclues gl.h, glu.h, ... others
# include <string>
# include <iostream>
# endif

#include "torus.h"
#include "moon.h"
#include "ship.h"
#include "camera.h"

using namespace std;

int view_state = 0;
int width = 1000, height = 700, x_0 = 0, y_0 = 0;
int mainWindow, subWindow1,subWindow2,subWindow3;
torus *tori1, *tori2, *tori3, *tori4;
moon *star;
ship *craft;
camera *player;
GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

void DisplayFunc0(void);
void DisplayFunc1(void);
void DisplayFunc2(void);
void DisplayFunc3(void);
void ReshapeFunc0(int width, int height);
void ReshapeFunc1(int width, int height);
void ReshapeFunc2(int width, int height);
void ReshapeFunc3(int width, int height);
void glutAppInitialize(void);
void Keyboard0(unsigned char key, int x, int y);

void Keyboard0(unsigned char key, int x, int y)
{
	cout << "x = " << x << " y = " << y << endl;
	switch(key)
	{
	case 118:
		if(view_state==0)
		{
			cout << "Setting view state to third person" << endl;
			view_state = 1;
		}
		else
		{
			cout << "Setting view state to first person" << endl;
			view_state = 0;
		}
		glutSetWindow(subWindow1);
		glutPostRedisplay();
		break;
	}
}

void ReshapeFunc0(int width, int height)
{
	if(width < 995 && height < 700)
	{
		width = 995;
		height = 700;
		glutSetWindow(mainWindow);
		glutPositionWindow(x_0 + 5, y_0 + 30);
		glutReshapeWindow(width, height);
		ReshapeFunc1(width, height);
		ReshapeFunc2(width, height);
		ReshapeFunc3(width, height);
	}
	else if(height < 700)
	{
		height = 700;
		glutSetWindow(mainWindow);
		glutPositionWindow(x_0, y_0);
		glutReshapeWindow(width, height);
		ReshapeFunc1(width, height);
		ReshapeFunc2(width, height);
		ReshapeFunc3(width, height);
	}
	else if(width < 995)
	{
		width = 995;
		glutSetWindow(mainWindow);
		glutPositionWindow(x_0, y_0);
		glutReshapeWindow(width, height);
		ReshapeFunc1(width, height);
		ReshapeFunc2(width, height);
		ReshapeFunc3(width, height);
	}
	else
	{
		ReshapeFunc1(width, height);
		ReshapeFunc2(width, height);
		ReshapeFunc3(width, height);
	}
}

void ReshapeFunc1(int width, int height)
{
	glutSetWindow(subWindow1);
	glutPositionWindow(x_0 + 10, y_0 + 10);
	glutReshapeWindow(width - (0.25 * width) - 10, height - 20);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	player->perspective(80.0, ((float)width - (float)width * .25) / ((float)height), 1.0, 10000000000.0);
}

void ReshapeFunc2(int width, int height)
{
	glutSetWindow(subWindow2);
	glutPositionWindow(width - (0.25 * width) + 10, y_0 + 10);
	glutReshapeWindow((0.25 * width - 20), height - (0.70 * height) - 20);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	player->perspective(90.0, ((float)width - (float)width * .25) / ((float)height), 1.0, 10000000000.0);
}

void ReshapeFunc3(int width, int height)
{
	glutSetWindow(subWindow3);
	glutPositionWindow(width - (0.25 * width) + 10, height - (0.70 * height));
	glutReshapeWindow((0.25 * width) - 20, (0.70 * height) - 10);
}

void DisplayFunc0(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void DisplayFunc1(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(view_state==0)
	{
		//*
		player->lookat(	craft->get_x_coord() + 50, craft->get_y_coord() + 300, craft->get_z_coord() + 50,
						craft->get_x_coord(), craft->get_y_coord(), craft->get_z_coord(),
						0.0000, 1.0000, 0.0000);
	}
	//*/
	//*
	else
	{
		player->lookat(	craft->get_x_coord()-200, craft->get_y_coord()-200, craft->get_z_coord()-200,
						0.0000, 0.0000, 0.0000,
						0.0000, 1.0000, 0.0000);
	}
	//*/
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	star->draw();
	tori1->draw();
	tori2->draw();
	tori3->draw();
	tori4->draw();
	craft->draw();
	glPopAttrib();
	glutSwapBuffers();
}

void DisplayFunc2(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//*
	gluLookAt(	0.0,		20100.0,		0.0,					// eye is at (x,y,z)
				0.0, 		0.0, 			0.0,      				// center is at (0,0,0)
				0.0, 		0.0,			1.0	);		   			// normal vector <x, y, z>
	//*/
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	star->draw();
	tori1->draw();
	tori2->draw();
	tori3->draw();
	tori4->draw();
	craft->draw();
	glPopAttrib();
	glutSwapBuffers();
}

void DisplayFunc3(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void glutAppInitialize(void)
{
	  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	  tori1 = new torus(100, 200, 10, 10, 3000.0, 0.0, 0.0, 90, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	  tori2 = new torus(100, 300, 10, 10, 0.0, 0.0, 5000.0, 90.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	  tori3 = new torus(100, 700, 10, 10, -9000.0, 0.0, 0.0, 90.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	  tori4 = new torus(100, 500, 10, 10, 0.0, 0.0, -12000.0, 90.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	  star = new moon(2000.0, 90, 90, 0.0, 0.0, 0.0, 90.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	  craft = new ship(100, 300, 50, 40, 7000.0, 7000.0, 7000.0, -140.0, -0.00, 0.50, -0.20, 1.0, 1.0, 1.0);
	  player = new camera();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width ,height);
	glutAppInitialize();
	mainWindow = glutCreateWindow("Tori App");
	glutDisplayFunc(DisplayFunc0);								// Set display call back function
	glutReshapeFunc(ReshapeFunc0);
	glutKeyboardFunc(Keyboard0);

	subWindow1 = glutCreateSubWindow(mainWindow, x_0 + 10, y_0 + 10, width - (0.25 * width) - 10, height - 20);
	glutDisplayFunc(DisplayFunc1);								// Set display call back function
	glutKeyboardFunc(Keyboard0);

	subWindow2 = glutCreateSubWindow(mainWindow, width - (0.25 * width) + 10, y_0 + 10, (0.25 * width - 25), height - (0.70 * height) - 20);
	glutDisplayFunc(DisplayFunc2);							// Set call back function
	glutKeyboardFunc(Keyboard0);

	subWindow3 = glutCreateSubWindow(mainWindow, width - (0.25 * width) + 10, height - (0.70 * height), (0.25 * width) - 20, (0.70 * height) - 10);
	glutDisplayFunc(DisplayFunc3);							// Set call back function
	glutKeyboardFunc(Keyboard0);

	glutMainLoop();
	return(0);
}


























