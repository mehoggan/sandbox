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
# include <GL/glut.h>  											// glut.h includes gl.h and glu.h
# endif

# if defined (__Linux__)  										// Linux
# include <GL/glut.h>  											// inclues gl.h, glu.h, ... others
# include <string>
# include <iostream>
# endif

#include "ship.h"
#include "torus.h"
#include "torpedo.h"
#include "skybox.h"
#include "explosion.h"

using namespace std;
/*
 *	Annoying variables
 */
bool print[12];

/*
 *	Constant Variables
 */
const GLdouble PI = 3.14159265358979323846264338;

/*
 *	Global Variables
 */
//	Standard Variables	//
GLfloat width = 1200, height = 700, x_0 = 0, y_0 = 0;
int x_light = 5.0, y_light = 5.0, z_light = 5.0;
int mainWindow;
int modelListId = 1;	//	Display List Id for Ship
//	Actual Game Objects	//
ship* craft;
torus *torus1, *torus2, *torus3, *torus4;
skybox* outer_space;
//	Game Variables	//
float speed = 60.0;
float angle = 0.5;
float torpedo_speed = 60.0; 
GLfloat TQ = 40;
GLfloat FPS = 25;
GLfloat MILISEC = 1000;
int frameCount = 0; 
int intervalTimerCalls = 0;
const int TRAINEE_TIME = 80;
const int PILOT_TIME = 60;
const int ACE_TIME = 40;
int TQ_INCREMENT = 20;
int rot1=1;
int rot2=rot1+20;
int rot3=rot2+20;
int rot4=rot3+20;
//	Keyboard Trackers	//
bool keyboardNormal[128];
bool keyboardSpec[16];
bool keyboardMods[5];
//	Game States	//
enum GAMESTATE {PAUSED, PLAY, GAMEOVER, VICTORY};
int pause = PLAY;
enum PLAYVIEWSTATE {NORMALVIEW, TORUS1VIEW, TORUS2VIEW, TORUS3VIEW, TORUS4VIEW};
int playview = NORMALVIEW;
enum CAMERAVIEWSTATE {NORMALCAMERA, SUNCAMERA, TORUS1CAMERA, TORUS2CAMERA, TORUS3CAMERA, TORUS4CAMERA};
int cameraview = NORMALCAMERA;
enum GRAVITY {ON, OFF};
int gravity = ON;
enum COCKPIT {INSIDE, OUTSIDE};
int cockpitview = OUTSIDE;
enum DEBUG {NORMAL, TORPEDO};
int debug_mode = NORMAL;
//	Torpedo and Tori Tracker	//
int torpedos_shot = 0;
torpedo** torpedos;
bool torpedo_shot_and_alive[12];
bool torpedo_draw[12];
int torpedo_count_out_timer[12];
int* torus_tracker;
int torpedo_alive = 100;
explosion** explosions;
bool explosion_active[12];
int explosion_timer[12];
int explosions_count;

/*
 *	Prototypes Global Call Back Functions
 */
void draw(void);
void resize(int width, int height);
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void SpecKeyDown(int key, int x, int y);
void SpecKeyUp(int key, int x, int y);
void Animation(int T);

/*
 *	Prototypes for Non-Callback Functions
 */
void glutAppInitialize(void);
void printKeysPressed();
void updateCommands();
void colisionDetection();
void displayAllText();


/*
 *	Call Back Function Definitions For Draw and Redraw, Keyboard Functions Below
 */
void resize(int w, int h){
	width = 1200; 
	height = 700;
	glutReshapeWindow(width, height);
	/*
	width=w;
	height=h;
	//*/
}

void draw(void){
	glEnable(GL_SCISSOR_TEST);
	glClearDepth(1.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	GLfloat color[4] = {1.0, 0.0, 0.0, 1.0};
	GLfloat color2[4] = {0.8, 0.2, 0.1, 1.0};

	updateCommands();
	colisionDetection();

	/*
	 *	THE MAIN VIEW PORT
	 */
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, (2*(float)width)/3.0, height);
		gluPerspective(45, ((float)width/(1.5*(float)height)), 1, 2000000000);
	glMatrixMode(GL_MODELVIEW);
	glScissor(0, 0, (2*(float)width)/3.0, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if(cameraview == SUNCAMERA){
		gluLookAt(	3000,	3000,	3000,
					0,		0,		0,
					0,		1,		0);
	}else if(torus1 != NULL && cameraview == TORUS1CAMERA){
		gluLookAt(	torus1->get_X_Pos() + torus1->get_X_Up()*200 + torus1->get_X_At() * 4000,		
					torus1->get_Y_Pos() + torus1->get_Y_Up()*200 + torus1->get_Y_At() * 4000,		
					torus1->get_Z_Pos() + torus1->get_Z_Up()*200 + torus1->get_Z_At() * 4000,
					torus1->get_X_Pos() + torus1->get_X_At()*200,	
					torus1->get_Y_Pos() + torus1->get_Y_At()*200,	    
					torus1->get_Z_Pos() + torus1->get_Z_At()*200, 
					torus1->get_X_Up(),								
					torus1->get_Y_Up(),								
					torus1->get_Z_Up()		);
	}else if(torus2 != NULL && cameraview == TORUS2CAMERA){
		gluLookAt(	torus2->get_X_Pos() + torus2->get_X_Up()*200 + torus2->get_X_At() * 4000,		
					torus2->get_Y_Pos() + torus2->get_Y_Up()*200 + torus2->get_Y_At() * 4000,		
					torus2->get_Z_Pos() + torus2->get_Z_Up()*200 + torus2->get_Z_At() * 4000,
					torus2->get_X_Pos() + torus2->get_X_At()*200,	
					torus2->get_Y_Pos() + torus2->get_Y_At()*200,	    
					torus2->get_Z_Pos() + torus2->get_Z_At()*200, 
					torus2->get_X_Up(),								
					torus2->get_Y_Up(),								
					torus2->get_Z_Up()		);
	}else if(torus3 != NULL && cameraview == TORUS3CAMERA){
		gluLookAt(	torus3->get_X_Pos() + torus3->get_X_Up()*200 + torus3->get_X_At() * 4000,		
					torus3->get_Y_Pos() + torus3->get_Y_Up()*200 + torus3->get_Y_At() * 4000,		
					torus3->get_Z_Pos() + torus3->get_Z_Up()*200 + torus3->get_Z_At() * 4000,
					torus3->get_X_Pos() + torus3->get_X_At()*200,	
					torus3->get_Y_Pos() + torus3->get_Y_At()*200,	    
					torus3->get_Z_Pos() + torus3->get_Z_At()*200, 
					torus3->get_X_Up(),								
					torus3->get_Y_Up(),								
					torus3->get_Z_Up()		);
	}else if(torus4 != NULL && cameraview == TORUS4CAMERA){
		gluLookAt(	torus4->get_X_Pos() + torus4->get_X_Up()*200 + torus4->get_X_At() * 4000,		
					torus4->get_Y_Pos() + torus4->get_Y_Up()*200 + torus4->get_Y_At() * 4000,		
					torus4->get_Z_Pos() + torus4->get_Z_Up()*200 + torus4->get_Z_At() * 4000,
					torus4->get_X_Pos() + torus4->get_X_At()*200,	
					torus4->get_Y_Pos() + torus4->get_Y_At()*200,	    
					torus4->get_Z_Pos() + torus4->get_Z_At()*200, 
					torus4->get_X_Up(),								
					torus4->get_Y_Up(),								
					torus4->get_Z_Up()		);
	}else{
		cameraview = NORMALCAMERA;
		if(cockpitview == OUTSIDE){
			gluLookAt(	craft->get_X_Pos() + craft->get_X_Up()*1000 - craft->get_X_At() * 1500,		
						craft->get_Y_Pos() + craft->get_Y_Up()*1000 - craft->get_Y_At() * 1500,		
						craft->get_Z_Pos() + craft->get_Z_Up()*1000 - craft->get_Z_At() * 1500,
						craft->get_X_Pos() + craft->get_X_At()*1200,	
						craft->get_Y_Pos() + craft->get_Y_At()*1200,	    
						craft->get_Z_Pos() + craft->get_Z_At()*1200, 
						craft->get_X_Up(),								
						craft->get_Y_Up(),								
						craft->get_Z_Up()		);
		}else{
			gluLookAt(	craft->get_X_Pos() + craft->get_X_At() * 900,		
						craft->get_Y_Pos() + craft->get_Y_At() * 900,
						craft->get_Z_Pos() + craft->get_Z_At() * 900,
						craft->get_X_Pos() + craft->get_X_At() * 10000,	
						craft->get_Y_Pos() + craft->get_Y_At() * 10000,	    
						craft->get_Z_Pos() + craft->get_Z_At() * 10000, 
						craft->get_X_Up(),								
						craft->get_Y_Up(),								
						craft->get_Z_Up()		);
		}
	}
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	for(int x = 0; x < 12; x++){
		if(torpedo_shot_and_alive[x] && torpedo_draw[x]){
			torpedos[x]->draw();
		}
	}
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for(int i = 0; i < 12; i++){
		if(explosion_active[i]){
			explosions[i]->draw(explosion_timer[i]+100,explosion_timer[i]+50,explosion_timer[i]);
		}
	}
	glDisable (GL_BLEND);
	craft->draw();
	if(torus1 != NULL){
		torus1->draw("mars");
	}
	if(torus2 != NULL){
		torus2->draw("earth");
	}
	if(torus3 != NULL){
		torus3->draw("jupiter");
	}
	if(torus4 != NULL){
		torus4->draw("golfball");
	}
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
		glutSolidSphere(2000.0, 90, 180);
	glPopMatrix();
	glPopAttrib();
	
	/*
	 *	SKYBOX 
	 */
	outer_space->draw();
	/*
	 *	END OF SKYBOX
	 */

	/*
	 *	THE SECOND VIEW PORT
	 */
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport((2*(float)width)/6, (2*(float)height/6), width , height);
		gluPerspective(135, (((float)width))/(((float)height)), 1, 2000000000);
	glMatrixMode(GL_MODELVIEW);
	glScissor((2*(float)width)/3, (2*(float)height/3), width , height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	0.0, 16000.0, 0.0,
				0.0, 0.0, 0.0,
				0.0, 0.0, -1.0	);
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	for(int x = 0; x < 12; x++){
		if(torpedo_shot_and_alive[x] && torpedo_draw[x]){
			torpedos[x]->draw();
		}
	}
	glEnable (GL_BLEND);
	for(int i = 0; i < 12; i++){
		if(explosion_active[i]){
			explosions[i]->draw(explosion_timer[i]+100,explosion_timer[i]+50,explosion_timer[i]);
		}
	}
	glDisable (GL_BLEND);	
	craft->draw();
	if(torus1 != NULL){
		torus1->draw("mars");
	}
	if(torus2 != NULL){
		torus2->draw("earth");
	}
	if(torus3 != NULL){
		torus3->draw("jupiter");
	}
	if(torus4 != NULL){
		torus4->draw("golfball");
	}
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
		glutSolidSphere(2000.0, 90, 180);
	glPopMatrix();
	glPopAttrib();

	/*
	 *	SKYBOX 
	 */
	outer_space->draw();
	/*
	 *	END OF SKYBOX
	 */
	
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	/*
	 *	THE THIRD VIEW PORT
	 */
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport((2*(float)width)/6, 0, width , (2*(float)height/3.0));
		gluPerspective(45, ((1.5*(float)width))/(((float)height)), 1, 2000);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glScissor((2*(float)width)/3, 0, width , (2*(float)height/3));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	0.0, 0.0, 200.0,
				0.0, 0.0, 0.0,
				0.0, 1.0, 0.0	);
	displayAllText();
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	/*
	 *	THE BORDERS
	 */
	//*
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(2.0*(float)width/3 - 1.0, 0, 10, (float)height);
		gluPerspective(45, ((float)width/(float)height), 1, 20000.0);
	glMatrixMode(GL_MODELVIEW);
	glScissor(2.0*(float)width/3 - 1.0, 0, 10, (float)height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	0.0,	0.0,	20000.0,
				0.0,	0.0,	0.0,
				0.0,	1.0,	0.0	);
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	glPushMatrix();
		GLfloat color3[4]={1.0, 1.0, 1.0, 1.0};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color3);
		glLineWidth(5.0);
		glBegin(GL_LINES);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, -4000000000.0, 0.0);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 4000000000.0, 0.0);
		glEnd();
	glPopMatrix();
	glPopAttrib();
	//*/

	glDisable(GL_SCISSOR_TEST);
	glFlush();
	glutSwapBuffers();
	playview = NORMALVIEW;
}

void Animation(int T){
	intervalTimerCalls++;
	frameCount++;
	/*
	if (intervalTimerCalls * TQ >= 1000) {
		cout << "fps: " << frameCount << endl;
		intervalTimerCalls = frameCount = 0;
	}
	//*/

	glutPostRedisplay();
	glutTimerFunc(TQ,Animation,0);
	if(pause == VICTORY){

	}else if(pause == PLAY && pause != GAMEOVER){
		if(torus1 != NULL){
			torus1->rotate(.004000	/*.23*/);
		}
		if(torus2 != NULL){
			torus2->rotate(.002619	/*.15*/);
		}
		if(torus3 != NULL){
			torus3->rotate(.001921	/*.11*/);
		}
		if(torus4 != NULL){
			torus4->rotate(.001397	/*.08*/);
		}

		/* Apply Gravity to Ship */
		if(gravity==ON){
			GLfloat vector[3];
			vector[0] = craft->get_X_Pos();
			vector[1] = craft->get_Y_Pos();
			vector[2] = craft->get_Z_Pos();
			GLfloat distance = sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
			GLfloat magnitude = distance;
			vector[0] = -1*vector[0]/magnitude;
			vector[1] = -1*vector[1]/magnitude;
			vector[2] = -1*vector[2]/magnitude;
			craft->set_X_Pos(craft->get_X_Pos() + vector[0]*(90000000/(distance*distance)));	//Matrix[12] = Matrix[12] + Matrix[8]*10;
			craft->set_Y_Pos(craft->get_Y_Pos() + vector[1]*(90000000/(distance*distance)));	//Matrix[13] = Matrix[13] + Matrix[9]*10;
			craft->set_Z_Pos(craft->get_Z_Pos() + vector[2]*(90000000/(distance*distance)));	//Matrix[13] = Matrix[13] + Matrix[9]*10;
		}

		/*	All Torpedo Effects	*/
		for(int i = 0; i < 12; i++){
			if(torpedo_shot_and_alive[i]){
				if(torpedos[i] != NULL){
					GLfloat sun_distance = sqrt(torpedos[i]->get_X_Pos()*torpedos[i]->get_X_Pos() + 
												torpedos[i]->get_Y_Pos()*torpedos[i]->get_Y_Pos() +
												torpedos[i]->get_Z_Pos()*torpedos[i]->get_Z_Pos()	);
					if(sun_distance <= 2050){
						//cout << "Torpedo " << i+1 << " hit the sun " << endl;
						torpedo_shot_and_alive[i] = false;
						if(torpedos[i] != NULL){
							delete torpedos[i];
							torpedos[i] = NULL;
						}
					}
				}
				if(!(torpedos[i] == NULL) && (torpedo_shot_and_alive[i])){
					if(!(torpedos[i]->get_Target() == NULL)){
						torpedos[i]->seek_and_destroy();
					}
					torpedos[i]->set_X_Pos(torpedos[i]->get_X_Pos() + torpedos[i]->get_X_At() * torpedo_speed);		//Matrix[12] = Matrix[12] + Matrix[8]*10;
					torpedos[i]->set_Y_Pos(torpedos[i]->get_Y_Pos() + torpedos[i]->get_Y_At() * torpedo_speed);		//Matrix[13] = Matrix[13] + Matrix[9]*10;
					torpedos[i]->set_Z_Pos(torpedos[i]->get_Z_Pos() + torpedos[i]->get_Z_At() * torpedo_speed);		//Matrix[13] = Matrix[13] + Matrix[9]*10;
					if(gravity==ON){
						GLfloat vector[3];
						vector[0] = torpedos[i]->get_X_Pos();
						vector[1] = torpedos[i]->get_Y_Pos();
						vector[2] = torpedos[i]->get_Z_Pos();
						GLfloat distance = sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
						GLfloat magnitude = distance;
						vector[0] = -1*vector[0]/magnitude;
						vector[1] = -1*vector[1]/magnitude;
						vector[2] = -1*vector[2]/magnitude;
						torpedos[i]->set_X_Pos(torpedos[i]->get_X_Pos() + vector[0]*(90000000/(distance*distance)));	//Matrix[12] = Matrix[12] + Matrix[8]*10;
						torpedos[i]->set_Y_Pos(torpedos[i]->get_Y_Pos() + vector[1]*(90000000/(distance*distance)));	//Matrix[13] = Matrix[13] + Matrix[9]*10;
						torpedos[i]->set_Z_Pos(torpedos[i]->get_Z_Pos() + vector[2]*(90000000/(distance*distance)));	//Matrix[13] = Matrix[13] + Matrix[9]*10;
					}
					torpedo_count_out_timer[i]++;
				}
				if(torpedo_count_out_timer[i] >= torpedo_alive){
					cout << "BOOOOOM Torpedo " << (i+1) << " exploded" << endl;
					torpedo_shot_and_alive[i] = false;
					torpedo_draw[i] = false;
					explosions[i] = new explosion(torpedos[i]->get_X_Pos(), torpedos[i]->get_Y_Pos(), torpedos[i]->get_Z_Pos());
					explosion_active[i] = true;
					explosions_count++;
					delete torpedos[i];
					torpedos[i] = NULL;
				}
			}
		}
		/*	All Exlposion Effects	*/
		for(int i=0; i<12; i++){
			if(explosion_active[i]){
				explosion_timer[i]+=10;
			}
			if(explosion_timer[i]==300){
				delete explosions[i];
				explosions[i]=NULL;
				explosion_active[i]=false;
			}
		}
	}
}

/*
 *	This is Where it All Starts
 */
int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(x_0, y_0);
	glutInitWindowSize(width ,height);
	mainWindow = glutCreateWindow("Tori App");
	/*
	 *	Set Call Back Functions
	 */
	glutDisplayFunc(draw);								
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecKeyDown);
	glutSpecialUpFunc(SpecKeyUp);
	glutTimerFunc(0,Animation,0);
	/*
	 *	Initialize App
	 */
	glutAppInitialize();
	craft->drawTriModel(modelListId, 10.0);
	/*
	 *	Release Control to Glut
	 */
	glutMainLoop();
	return(0);
}
/*=======================================================INITIALIZE FUNCTIONS=============================================================*/
void glutAppInitialize(void){
	//cout << "Initializing " << endl;
	craft = new ship(	100,		300,		40,			100,				// Cone attributes
						0.0,		1.0,		0.0,							// Color attributes
						/*0.0,		0.0,		7000.0,*/
						7000.0,		7000.0,		7000.0,	
						0.0,		0.0,		0.0			);					// Pitch, Roll, Yaw
	
	torus1 = new torus(	100,		200,		30,			70, 
						1.0,		0.0,		0.0,
						3000.0,		0.0,		0.0			); 
		
	torus2 = new torus(	100,		300,		30,			70, 
						0.0,		1.0,		0.0,
						0.0,		0.0,		5000.0		);

	torus3 = new torus(	100,		700,		30,			70, 
						0.0,		0.0,		1.0,
						-9000.0,	0.0,		0.0			); 

	torus4 = new torus(	100,		500,		30,			70, 
						0.8,		0.8,		0.8,
						0.0,		0.0,		-12000.0	);

	outer_space = new skybox(1000000);

	for(int x = 0; x < 128 ; x++){
		keyboardNormal[x] = false;
	}
	keyboardNormal[(int)'q'] = false;				//Game not paused
	keyboardNormal[(int)'g'] = true;				//Gravity is on
	keyboardNormal[(int)'v'] = true;				//View starts in cockpit
	keyboardNormal[(int)'d'] = true;				//Start of with normal debug text
	for(int x = 0; x < 16; x++){
		keyboardSpec[x] = false;
	}
	for(int x = 0; x < 4; x++){
		keyboardMods[x] = false;
	}

	/*	Generate Torpedo Data	*/
	torpedos = new torpedo*[12];
	torus_tracker = new int[12];
	explosions = new explosion*[12];
	explosions_count = 0;
	for(int i = 0; i < 12; i++){
		torpedo_shot_and_alive[i] = false;
		torpedo_count_out_timer[i] = 0;
		torpedo_draw[i] = false;
		torpedos[i] = NULL;
		explosions[i] = NULL;
		explosion_active[i] = false;
		explosion_timer[i] = 0;
		torus_tracker[i] = -1;
		print[i] = true;
	}

	GLfloat light_ambient0[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat light_diffuse0[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular0[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_position0[] = {20.0, 20.0, 20.0, 0.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	
	GLfloat light_ambient1[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat light_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular1[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_position1[] = {200.0, 200.0, 200.0, 1.0};
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	
	glBlendFunc (GL_ONE, GL_ONE);
}
/*=======================================================END INITIALIZE FUNCTIONS=========================================================*/
/*=======================================================UPDATE DISPLAY FUNCTIONS=========================================================*/
void updateCommands()
{
	if((torpedos_shot) >= 12){
		bool all_torpedos_gone = true;
		for(int z = 0; z < 12; z++){
			if(torpedos[z] != NULL){
				all_torpedos_gone = false;
			}
		}
		if(all_torpedos_gone){
			pause = GAMEOVER;
		}
	}
	/*
	 *	Teachers Specified Controls
	 */
	//	BASIC CONTROLS
	if(keyboardNormal[27] == true){
		exit(0);
	}
	if(pause != GAMEOVER){
		if(keyboardNormal[(int)'q'] == false && pause != GAMEOVER){
			pause = PLAY;
		}else{
			pause = PAUSED;
		}
	}
	if(torus1 == NULL && torus2 == NULL && torus3 == NULL && torus4 == NULL){
		pause = VICTORY;
	}
	if(keyboardNormal[(int)'d'] == true){
		debug_mode = NORMAL;
	}else{
		debug_mode = TORPEDO;
	}if(pause == VICTORY){
	}else if(pause == PLAY && pause != GAMEOVER){
		if(keyboardNormal[(int)'g'] == true){
			gravity = ON;
		}else{
			gravity = OFF;
		}
		if(keyboardNormal[(int)'v'] == true){
			cockpitview = INSIDE;
		}else{
			cockpitview = OUTSIDE;
		}
		if(keyboardNormal[(int)'f'] == true){
			if(torus1 == NULL && torus2 == NULL && torus3 == NULL && torus4 == NULL){
				pause = VICTORY;
			}else if(!(torpedos_shot >= 12) || torus1 != NULL || torus2 != NULL || torus3 != NULL || torus4 != NULL){
				//cout << "Torpedo " << (torpedos_shot + 1) << " Fired" << endl;
				torpedo_shot_and_alive[torpedos_shot] = true;
				torpedo_draw[torpedos_shot] = true;
				GLdouble distance1 = -1.0;
				GLdouble distance2 = -1.0;
				GLdouble distance3 = -1.0;
				GLdouble distance4 = -1.0;
				GLdouble min_dist = 100000000.0;
				torus* target = NULL;
				if(torus1 != NULL){
					double x_part = torus1->get_X_Pos() - craft->get_X_Pos();
					double y_part = torus1->get_Y_Pos() - craft->get_Y_Pos();
					double z_part = torus1->get_Z_Pos() - craft->get_Z_Pos();
					distance1 = sqrt(pow(x_part,2.0) + pow(y_part,2.0) + pow(z_part,2.0));
				}
				if(torus2 != NULL){
					double x_part = torus2->get_X_Pos() - craft->get_X_Pos();
					double y_part = torus2->get_Y_Pos() - craft->get_Y_Pos();
					double z_part = torus2->get_Z_Pos() - craft->get_Z_Pos();
					distance2 = sqrt(pow(x_part,2.0) + pow(y_part,2.0) + pow(z_part,2.0));
				}
				if(torus3 != NULL){ 
					double x_part = torus3->get_X_Pos() - craft->get_X_Pos();
					double y_part = torus3->get_Y_Pos() - craft->get_Y_Pos();
					double z_part = torus3->get_Z_Pos() - craft->get_Z_Pos();
					distance3 = sqrt(pow(x_part,2.0) + pow(y_part,2.0) + pow(z_part,2.0));
				}
				if(torus4 != NULL){
					double x_part = torus4->get_X_Pos() - craft->get_X_Pos();
					double y_part = torus4->get_Y_Pos() - craft->get_Y_Pos();
					double z_part = torus4->get_Z_Pos() - craft->get_Z_Pos();
					distance4 = sqrt(pow(x_part,2.0) + pow(y_part,2.0) + pow(z_part,2.0));
				}
				if(distance1 != -1.0 && torus1 != NULL){
					min_dist = distance1;
					target = torus1;
					torus_tracker[torpedos_shot] = 1;
				}
				if(distance2 != -1.0 && distance2 < min_dist && torus2 != NULL){
					min_dist = distance2;
					target = torus2;
					torus_tracker[torpedos_shot] = 2;
				}
				if(distance3 != -1.0 && distance3 < min_dist && torus3 != NULL){
					min_dist = distance3;
					target = torus3;
					torus_tracker[torpedos_shot] = 3;
				}
				if(distance4 != -1.0 && distance4 < min_dist && torus4 != NULL){
					min_dist = distance4;
					target = torus4;
					torus_tracker[torpedos_shot] = 4;
				}
				torpedos[torpedos_shot] = new torpedo(	50.0, 30.0, 90.0, 1.0, 0.0, 0.0, 
														craft->get_X_Pos() + craft->get_X_At() * 700,
														craft->get_Y_Pos() + craft->get_Y_At() * 700,
														craft->get_Z_Pos() + craft->get_Z_At() * 700,
														craft->get_X_Right(), craft->get_Y_Right(), craft->get_Z_Right(),
														craft->get_X_Up(), craft->get_Y_Up(), craft->get_Z_Up(),
														craft->get_X_At(), craft->get_Y_At(), craft->get_Z_At(),
														target);
				keyboardNormal[(int)'f'] = false;		//	Prevent Torpedo Spam
			}
			++torpedos_shot;
		}
		if(keyboardNormal[(int)'t'] == true){
			// Handled below on key up for accuracy
		}
		//	MOVEMENT KEYS
		if(keyboardSpec[13] == true && !keyboardMods[2]){
			craft->set_X_Pos(craft->get_X_Pos() + craft->get_X_At() * speed);	//Matrix[12] = Matrix[12] + Matrix[8]*10;
			craft->set_Y_Pos(craft->get_Y_Pos() + craft->get_Y_At() * speed);	//Matrix[13] = Matrix[13] + Matrix[9]*10;
			craft->set_Z_Pos(craft->get_Z_Pos() + craft->get_Z_At() * speed);	//Matrix[13] = Matrix[13] + Matrix[9]*10;
		}
		if(keyboardSpec[15] == true && !keyboardMods[2]){
			craft->set_X_Pos(craft->get_X_Pos() - craft->get_X_At() * speed);	//Matrix[12] = Matrix[12] - Matrix[8]*10;
			craft->set_Y_Pos(craft->get_Y_Pos() - craft->get_Y_At() * speed);	//Matrix[13] = Matrix[13] - Matrix[9]*10;
			craft->set_Z_Pos(craft->get_Z_Pos() - craft->get_Z_At() * speed);	//Matrix[13] = Matrix[13] - Matrix[9]*10;
		}
		if(keyboardSpec[12] == true && !keyboardMods[2]){
			craft->turn(angle, 0.0, 1.0, 0.0);
		}
		if(keyboardSpec[14] == true && !keyboardMods[2]){
			craft->turn(-1 * angle, 0.0, 1.0, 0.0);
		}
		if(keyboardSpec[15] == true && keyboardMods[2]){
			craft->turn(-1 * angle, 1.0, 0.0, 0.0);
		}
		if(keyboardSpec[13] == true && keyboardMods[2]){
			craft->turn(angle, 1.0, 0.0, 0.0);
		}
		if(keyboardSpec[14] == true && keyboardMods[2]){
			craft->turn(-1 * angle, 0.0, 0.0, 1.0);
		}
		if(keyboardSpec[12] == true && keyboardMods[2]){
			craft->turn(angle, .0, 0.0, 1.0);
		}
		// CAMERA VIEW
		if(keyboardSpec[2] == true){
			cameraview = SUNCAMERA;
		}else if(keyboardSpec[3] == true){
			cameraview = TORUS1CAMERA;
		}else if(keyboardSpec[4] == true){
			cameraview = TORUS2CAMERA;
		}else if(keyboardSpec[5] == true){
			cameraview = TORUS3CAMERA;
		}else if(keyboardSpec[6] == true){
			cameraview = TORUS4CAMERA;
		}else if(!keyboardSpec[2] || !keyboardSpec[3] || !keyboardSpec[4] || !keyboardSpec[5] || !keyboardSpec[6]){
			cameraview = NORMALCAMERA;
		}
		//	PLAY WINDOW VIEW
		if(torus1 != NULL && keyboardSpec[8] == true){
			//	FIRST SET CRAFT NEXT TO TORI
			craft->orient_ship(torus1);
			playview = TORUS1VIEW;
		}else if(torus2 != NULL && keyboardSpec[9] == true){
			craft->orient_ship(torus2);
			playview = TORUS2VIEW;
		}else if(torus3 != NULL && keyboardSpec[10] == true){
			craft->orient_ship(torus3);
			playview = TORUS3VIEW;
		}else if(torus4 != NULL && keyboardSpec[11] == true){
			craft->orient_ship(torus4);
			playview = TORUS4VIEW;;
		}else if(!keyboardSpec[7] || !keyboardSpec[8] || !keyboardSpec[9] || !keyboardSpec[10] || !keyboardSpec[11]){
			playview = NORMALVIEW;
		}
	}
}
/*=======================================================COLISION FUNCTIONS===============================================================*/
bool impactToShip(double FROM_X, double FROM_Y, double FROM_Z, double min_distance){
	bool ret = false;
	if((	sqrt(pow((double)(craft->get_X_Pos()-FROM_X), 2.0) + 
				 pow((double)(craft->get_Y_Pos()-FROM_Y), 2.0) + 
				 pow((double)(craft->get_Z_Pos()-FROM_Z), 2.0))) <= min_distance){
		ret = true;	
	}if((	sqrt(pow((double)((craft->get_X_Pos()+craft->get_X_At()*250)-FROM_X), 2.0) + 
				 pow((double)((craft->get_Y_Pos()+craft->get_Y_At()*250)-FROM_Y), 2.0) +
				 pow((double)((craft->get_Z_Pos()+craft->get_Z_At()*250)-FROM_Z), 2.0))) <= min_distance){
		ret = true;
	}if((	sqrt(pow((double)((craft->get_X_Pos()+craft->get_X_Right()*400)-FROM_X), 2.0) + 
				 pow((double)((craft->get_Y_Pos()+craft->get_Y_Right()*400)-FROM_Y), 2.0) + 
				 pow((double)((craft->get_Z_Pos()+craft->get_Z_Right()*400)-FROM_Z), 2.0))) <= min_distance){ 
		ret = true;
	}if((	sqrt(pow((double)((craft->get_X_Pos()-craft->get_X_Right()*400)-FROM_X), 2.0) + 
				 pow((double)((craft->get_Y_Pos()-craft->get_Y_Right()*400)-FROM_Y), 2.0) + 
				 pow((double)((craft->get_Z_Pos()-craft->get_Z_Right()*400)-FROM_Z), 2.0))) <= min_distance){
		ret = true;
	}if((	sqrt(pow((double)((craft->get_X_Pos()+craft->get_X_Up()*400)-FROM_X), 2.0) + 
				 pow((double)((craft->get_Y_Pos()+craft->get_Y_Up()*400)-FROM_Y), 2.0) + 
				 pow((double)((craft->get_Z_Pos()+craft->get_Z_Up()*400)-FROM_Z), 2.0))) <= min_distance){
		ret = true;
	}if((	sqrt(pow((double)((craft->get_X_Pos()-craft->get_X_Up()*400)-FROM_X), 2.0) + 
				 pow((double)((craft->get_Y_Pos()-craft->get_Y_Up()*400)-FROM_Y), 2.0) + 
				 pow((double)((craft->get_Z_Pos()-craft->get_Z_Up()*400)-FROM_Z), 2.0))) <= min_distance){
		ret = true;
	}
	return ret;
}
void colisionDetection(){
	/*
	 *	Ship's Colision Tests With Sun
	 */
	if(impactToShip(0.0, 0.0, 0.0, 2000.0)){
		pause = GAMEOVER;
	}

	/*
	 *	Ship's Colision Tests With Tori1
	 */
	if(torus1 != NULL){
		if(sqrt(pow((double)(craft->get_X_Pos()-torus1->get_X_Pos()), 2.0) +
				pow((double)(craft->get_Y_Pos()-torus1->get_Y_Pos()), 2.0) +
				pow((double)(craft->get_Z_Pos()-torus1->get_Z_Pos()), 2.0)) < 1000){
			bool test1 = impactToShip(torus1->get_X_Pos(), torus1->get_Y_Pos(), torus1->get_Z_Pos(), torus1->get_Inner_Radius());	
			bool test2 = impactToShip(torus1->get_X_Pos(), torus1->get_Y_Pos(), torus1->get_Z_Pos(), torus1->get_Outer_Radius());
			if(test1 || test2){
				pause = GAMEOVER;
			}
		}
	}
	/*
	 *	Ship's Colision Tests With Tori2
	 */
	if(torus2 != NULL){
		if(sqrt(pow((double)(craft->get_X_Pos()-torus2->get_X_Pos()), 2.0) +
				pow((double)(craft->get_Y_Pos()-torus2->get_Y_Pos()), 2.0) +
				pow((double)(craft->get_Z_Pos()-torus2->get_Z_Pos()), 2.0)) < 1500){
			bool test1 = impactToShip(torus2->get_X_Pos(), torus2->get_Y_Pos(), torus2->get_Z_Pos(), torus2->get_Inner_Radius());	
			bool test2 = impactToShip(torus2->get_X_Pos(), torus2->get_Y_Pos(), torus2->get_Z_Pos(), torus2->get_Outer_Radius());
			if(test1 || test2){
				pause = GAMEOVER;
			}
		}
	}
	/*
	 *	Ship's Colision Tests With Tori3
	 */
	if(torus3 != NULL){
		if(sqrt(pow((double)(craft->get_X_Pos()-torus3->get_X_Pos()), 2.0) +
				pow((double)(craft->get_Y_Pos()-torus3->get_Y_Pos()), 2.0) +
				pow((double)(craft->get_Z_Pos()-torus3->get_Z_Pos()), 2.0)) < 1500){
			bool test1 = impactToShip(torus3->get_X_Pos(), torus3->get_Y_Pos(), torus3->get_Z_Pos(), torus3->get_Inner_Radius());	
			bool test2 = impactToShip(torus3->get_X_Pos(), torus3->get_Y_Pos(), torus3->get_Z_Pos(), torus3->get_Outer_Radius());
			if(test1 || test2){
				pause = GAMEOVER;
			}
		}
	}
	/*
	 *	Ship's Colision Tests With Tori4
	 */
	if(torus4 != NULL){
		if(sqrt(pow((double)(craft->get_X_Pos()-torus4->get_X_Pos()), 2.0) +
				pow((double)(craft->get_Y_Pos()-torus4->get_Y_Pos()), 2.0) +
				pow((double)(craft->get_Z_Pos()-torus4->get_Z_Pos()), 2.0)) < 1500){
			bool test1 = impactToShip(torus4->get_X_Pos(), torus4->get_Y_Pos(), torus4->get_Z_Pos(), torus4->get_Inner_Radius());	
			bool test2 = impactToShip(torus4->get_X_Pos(), torus4->get_Y_Pos(), torus4->get_Z_Pos(), torus4->get_Outer_Radius());
			if(test1 || test2){
				pause = GAMEOVER;
			}
		}
	}
	/*
	 *	Torpedo's Test
	 */
	for(int i = 0; i < 12; i++){
		if(torpedo_shot_and_alive[i]){
			if(torpedos[i] != NULL){
				if((sqrt(	pow((double)(torpedos[i]->get_Target()->get_X_Pos() - torpedos[i]->get_X_Pos()), 2.0) + 
							pow((double)(torpedos[i]->get_Target()->get_Y_Pos() - torpedos[i]->get_Y_Pos()), 2.0) + 
							pow((double)(torpedos[i]->get_Target()->get_Z_Pos() - torpedos[i]->get_Z_Pos()), 2.0))) < 100){
					GLfloat distance = sqrt(	pow((double)(torpedos[i]->get_Target()->get_X_Pos() - torpedos[i]->get_X_Pos()), 2.0) + 
												pow((double)(torpedos[i]->get_Target()->get_Y_Pos() - torpedos[i]->get_Y_Pos()), 2.0) + 
												pow((double)(torpedos[i]->get_Target()->get_Z_Pos() - torpedos[i]->get_Z_Pos()), 2.0));
					cout << "The distance to target is " << distance << endl;
					torpedo_shot_and_alive[i] = false;
					if(torus_tracker[i] == 1){
						delete torus1;
						torus1 = NULL;
					}if(torus_tracker[i] == 2){
						delete torus2;
						torus2 = NULL;
					}if(torus_tracker[i] == 3){
						delete torus3;
						torus3 = NULL;
					}if(torus_tracker[i] == 4){
						delete torus4;
						torus4 = NULL;
					}
					torus_tracker[i] = NULL;
					explosions[i] = new explosion(torpedos[i]->get_X_Pos(), torpedos[i]->get_Y_Pos(), torpedos[i]->get_Z_Pos());
					explosion_active[i] = true;
					explosions_count++;
					delete torpedos[i];
					torpedos[i] = NULL;					
				}
			}
		}
	}
	if(torus1 == NULL && torus2 == NULL && torus3 == NULL && torus4 == NULL){
		pause = VICTORY;
	}
}
/*=======================================================KEYBOARD FUNCTIONS===============================================================*/
void KeyDown(unsigned char key, int x, int y){
	int mod = glutGetModifiers();
	if(mod == 0){
		keyboardMods[1] = false;
		keyboardMods[2] = false;
		keyboardMods[3] = false;
		keyboardMods[4] = false;
	}
	else{
		keyboardMods[mod] = true;
	}
	if(key == 'q'){
		if(keyboardNormal[(int)key] == false){
			keyboardNormal[(int)key] = true;
		}else{
			keyboardNormal[(int)key] = false;
		}
	}else if(key == 'g'){
		if(keyboardNormal[(int)key] == true){
			keyboardNormal[(int)key] = false;
		}else{
			keyboardNormal[(int)key] = true;
		}
	}else if(key == 'v'){
		if(keyboardNormal[(int)key] == true){
			keyboardNormal[(int)key] = false;
		}else{
			keyboardNormal[(int)key] = true;
		}
	}else if(key == 'd'){
		if(keyboardNormal[(int)key] == true){
			keyboardNormal[(int)key] = false;
		}else{
			keyboardNormal[(int)key] = true;
		}
	}else{										
		keyboardNormal[(int)key] = true;
	}
	draw();
}

void KeyUp(unsigned char key, int x, int y){
	int mod = glutGetModifiers();
	if(mod == 0){
		keyboardMods[1] = false;
		keyboardMods[2] = false;
		keyboardMods[3] = false;
		keyboardMods[4] = false;
	}else if(mod == 1){
		keyboardMods[0] = false;
		keyboardMods[2] = false;
		keyboardMods[3] = false;
		keyboardMods[4] = false;
	}else if(mod == 2){
		keyboardMods[0] = false;
		keyboardMods[1] = false;
		keyboardMods[3] = false;
		keyboardMods[4] = false;
	}else if(mod == 3){
		keyboardMods[0] = false;
		keyboardMods[1] = false;
		keyboardMods[2] = false;
		keyboardMods[4] = false;
	}else if(mod == 4){
		keyboardMods[0] = false;
		keyboardMods[1] = false;
		keyboardMods[2] = false;
		keyboardMods[3] = false;
	}
	if(key == 'q' || key == 'v' || key == 'g' || key == 'd'){
		// These keys are toggles only handled in key press
	}else if(key == 't'){
		if(TQ == TRAINEE_TIME){
			TQ = ACE_TIME;
		}else{
			TQ += TQ_INCREMENT;
		}
	}else{
		keyboardNormal[(int)key] = false;
	}
}

void SpecKeyDown(int key, int x, int y){
	glutIgnoreKeyRepeat(true);
	int mod = glutGetModifiers();
	if(mod == 0){
		keyboardMods[1] = false;
		keyboardMods[2] = false;
		keyboardMods[3] = false;
		keyboardMods[4] = false;
	}else{
		keyboardMods[mod] = true;
	}

	if(key >= 100){
		key = key - 87;
	}
	if(key == 2){
		keyboardSpec[2] = false;
		keyboardSpec[3] = false;
		keyboardSpec[4] = false;
		keyboardSpec[5] = false;
		if(keyboardSpec[2] == false){
			keyboardSpec[2] = true;
		}else{
			keyboardSpec[2] = false;
		}
	}else if(key == 3){
		keyboardSpec[2] = false;
		keyboardSpec[4] = false;
		keyboardSpec[5] = false;
		keyboardSpec[6] = false;
		if(keyboardSpec[3] == false){
			keyboardSpec[3] = true;
		}else{
			keyboardSpec[3] = false;
		}
	}else if(key == 4){
		keyboardSpec[2] = false;
		keyboardSpec[3] = false;
		keyboardSpec[5] = false;
		keyboardSpec[6] = false;
		if(keyboardSpec[4] == false){
			keyboardSpec[4] = true;
		}else{
			keyboardSpec[4] = false;
		}
	}else if(key == 5){
		keyboardSpec[2] = false;
		keyboardSpec[3] = false;
		keyboardSpec[4] = false;
		keyboardSpec[6] = false;
		if(keyboardSpec[5] == false){
			keyboardSpec[5] = true;
		}else{
			keyboardSpec[5] = false;
		}
	}else if(key == 6){
		keyboardSpec[2] = false;
		keyboardSpec[3] = false;
		keyboardSpec[4] = false;
		keyboardSpec[5] = false;
		if(keyboardSpec[6] == false){
			keyboardSpec[6] = true;
		}else{
			keyboardSpec[6] = false;
		}
	}else if(key == 9){
		keyboardSpec[8] = true;
	}else if(key == 10){
		keyboardSpec[9] = true;
	}else if(key == 11){
		keyboardSpec[10] = true;
	}else if(key == 12){
		keyboardSpec[11] = true;
	}
	if(key >= 100){
		key = key - 87;
	}
	if(key == 2 || key == 3 || key == 4 || key == 5 || key == 6 || key == 9 || key == 10 || key == 11 || key == 12){
	}else{
		keyboardSpec[key - 1] = true;
	}
	draw();
}

void SpecKeyUp(int key, int x, int y){
	int mod = glutGetModifiers();
	if(mod == 0){
		keyboardMods[1] = false;
		keyboardMods[2] = false;
		keyboardMods[3] = false;
		keyboardMods[4] = false;
	}
	mod = glutGetModifiers();
	if(mod == 1){
		keyboardMods[0] = false;
		keyboardMods[2] = false;
		keyboardMods[3] = false;
		keyboardMods[4] = false;
	}
	mod = glutGetModifiers();
	if(mod == 2){
		keyboardMods[0] = false;
		keyboardMods[1] = false;
		keyboardMods[3] = false;
		keyboardMods[4] = false;
	}
	mod = glutGetModifiers();
	if(mod == 3){
		keyboardMods[0] = false;
		keyboardMods[1] = false;
		keyboardMods[2] = false;
		keyboardMods[4] = false;
	}
	mod = glutGetModifiers();
	if(mod == 4){
		keyboardMods[0] = false;
		keyboardMods[1] = false;
		keyboardMods[2] = false;
		keyboardMods[3] = false;
	}
	if(key == 9){
		keyboardSpec[8] = false;
	}else if(key == 10){
		keyboardSpec[9] = false;
	}else if(key == 11){
		keyboardSpec[10] = false;
	}else if(key == 12){
		keyboardSpec[11] = false;
	}
	if(key >= 100){
		key = key - 87;
	}
	if(key == 1 || key == 2 || key == 3 || key == 4 || key == 5 || key == 8 || key == 9 || key == 10 || key == 11){
	}else{
		keyboardSpec[key - 1] = false;
	}
}
/*=======================================================END KEYBOARD FUNCTIONS===========================================================*/
/*=======================================================DISPLAY TEXT FUNCTION============================================================*/
void displayAllText(){
	int y_pos = 60;
	int font=(int)GLUT_BITMAP_8_BY_13;
	if(debug_mode == NORMAL){
		/*	LINE 1	*/
		char* player_type;
		if(TQ == TRAINEE_TIME){
			player_type = "TRAINEE";
		}else if(TQ == PILOT_TIME){
			player_type = "PILOT";
		}else if(TQ == ACE_TIME){
			player_type = "ACE";
		}

		char string1[1024];
		sprintf_s(string1, " Player Type: %s", player_type);
		char* iterator1 = string1;
		int x_pos = -72;
		while(*(iterator1) != '\0'){
			glRasterPos2f(x_pos, y_pos);
			glutBitmapCharacter((void*)font, *(iterator1));
			x_pos += 4;
			iterator1++;
		}

		/*	LINE 2	*/
		char string2[1024];
		sprintf_s(string2, " Time Quantum: %f", TQ);
		char* iterator2 = string2;
		x_pos = -72;
		y_pos -= 10;
		while(*(iterator2) != '\0'){
			glRasterPos2f(x_pos, y_pos);
			glutBitmapCharacter((void*)font, *(iterator2));
			x_pos += 4;
			iterator2++;
		}

		/*	LINE 3	*/
		char* grav_option;
		if(gravity == ON){
			grav_option = "ON";
		}else{
			grav_option = "OFF";
		}
		char string3[1024];
		sprintf_s(string3, " Gravity: %s", grav_option);
		char* iterator3 = string3;
		x_pos = -72;
		y_pos -= 10;
		while(*(iterator3) != '\0'){
			glRasterPos2f(x_pos, y_pos);
			glutBitmapCharacter((void*)font, *(iterator3));
			x_pos += 4;
			iterator3++;
		}

		/*	LINE 4	*/
		char* play_view_option;
		if(playview == NORMALVIEW){
			play_view_option = "NORMAL VIEW";
		}else if(playview == TORUS1VIEW){
			play_view_option = "TORUS1 VIEW";
		}else if(playview == TORUS2VIEW){
			play_view_option = "TORUS2 VIEW";
		}else if(playview == TORUS3VIEW){
			play_view_option = "TORUS3 VIEW";
		}else if(playview == TORUS4VIEW){
			play_view_option = "TORUS4 VIEW";
		}

		char string4[1024];
		sprintf_s(string4, " Ships View: %s", play_view_option);
		char* iterator4 = string4;
		x_pos = -72;
		y_pos -= 10;
		while(*(iterator4) != '\0'){
			glRasterPos2f(x_pos, y_pos);
			glutBitmapCharacter((void*)font, *(iterator4));
			x_pos += 4;
			iterator4++;
		}

		/*	LINE 5	*/
		char* camera_view_option;
		if(cameraview == NORMALCAMERA){
			camera_view_option = "SHIP";
		}else if(cameraview == SUNCAMERA){
			camera_view_option = "SUN";
		}else if(cameraview == TORUS1CAMERA){
			camera_view_option = "TORUS1";
		}else if(cameraview == TORUS2CAMERA){
			camera_view_option = "TORUS2";
		}else if(cameraview == TORUS3CAMERA){
			camera_view_option = "TORUS3";
		}else if(cameraview == TORUS4CAMERA){
			camera_view_option = "TORUS4";
		}

		char string5[1024];
		sprintf_s(string5, " Camera View: %s", camera_view_option);
		char* iterator5 = string5;
		x_pos = -72;
		y_pos -= 10;
		while(*(iterator5) != '\0'){
			glRasterPos2f(x_pos, y_pos);
			glutBitmapCharacter((void*)font, *(iterator5));
			x_pos += 5;
			iterator5++;
		}

		/*	LINE 6	*/
		char string6[1024];
		sprintf_s(string6, " Frames/Sec: %f", (1000/TQ));
		char* iterator6 = string6;
		x_pos = -72;
		y_pos -= 10;
		while(*(iterator6) != '\0'){
			glRasterPos2f(x_pos, y_pos);
			glutBitmapCharacter((void*)font, *(iterator6));
			x_pos += 4;
			iterator6++;
		}

		/*	LINE 7	*/
		char* play_state;
		if(pause == PLAY){
			play_state = "PLAY";
		}else if(pause == PAUSED){
			play_state = "PAUSED";
		}else if(pause == GAMEOVER){
			play_state = "GAME OVER";
		}else if(pause == VICTORY){
			play_state = "VICTORY";
		}

		char string7[1024];
		sprintf_s(string7, " Game State: %s", play_state);
		char* iterator7 = string7;
		x_pos = -72;
		y_pos -= 10;
		while(*(iterator7) != '\0'){
			glRasterPos2f(x_pos, y_pos);
			glutBitmapCharacter((void*)font, *(iterator7));
			x_pos += 4;
			iterator7++;
		}

		/*	LINE 8	*/
		char string8[1024];
		sprintf_s(string8, " Torpedos:" );
		char* iterator8 = string8;
		x_pos = -72;
		y_pos -= 10;
		while(*(iterator8) != '\0'){
			glRasterPos2f(x_pos, y_pos);
			glutBitmapCharacter((void*)font, *(iterator8));
			x_pos += 4;
			iterator8++;
		}
		for(int x = torpedos_shot; x < 12; x++){
			glBegin(GL_QUADS);
				glVertex3f((float)(x_pos + 1.0), (float)(y_pos+5), 0.0f);
				glVertex3f((float)(x_pos + 1.0), (float)(y_pos-1), 0.0f);
				glVertex3f((float)(x_pos + 2.0), (float)(y_pos-1), 0.0f);
				glVertex3f((float)(x_pos + 2.0), (float)(y_pos+5), 0.0f);
			glEnd();
			x_pos += 5;
		}

		/*	LINE 9	*/
		char string9[1024];
		sprintf_s(string9, " Tories:" );
		char* iterator9 = string9;
		x_pos = -72;
		y_pos -= 10;
		while(*(iterator9) != '\0'){
			glRasterPos2f(x_pos, y_pos);
			glutBitmapCharacter((void*)font, *(iterator9));
			x_pos += 4;
			iterator9++;
		}

		glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);	
		GLfloat x_o = -32;
		GLfloat y_o = -20;
		rot1+=20;
		rot2+=20;
		rot3+=20;
		rot4+=20;
		if(rot1>360)rot1-=360;
		if(rot2>360)rot2-=360;
		if(rot3>360)rot3-=360;
		if(rot4>360)rot4-=360;
		if(torus1 != NULL) {
			glPushMatrix();
				GLfloat color2[4] = {1.0, 0.0, 0.0, 1.0};
				glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
				glTranslatef(x_o, y_o, 0.0);
				glRotatef(rot1,0.0,1.0,0.0);
				glutSolidTorus(2.0, 4.0, 2.0, 30.0);
			glPopMatrix();
			x_o += 20;
		}
		if(torus2 != NULL) {
			glPushMatrix();
				GLfloat color2[4] = {0.0, 1.0, 0.0, 1.0};
				glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
				glTranslatef(x_o, y_o, 0.0);
				glRotatef(rot2,0.0,1.0,0.0);
				glutSolidTorus(2.0, 4.0, 2.0, 30.0);
			glPopMatrix();
			x_o += 20;
		}
		if(torus3 != NULL) {
			glPushMatrix();
				GLfloat color2[4] = {0.0, 0.0, 1.0, 1.0};
				glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
				glTranslatef(x_o, y_o, 0.0);
				glRotatef(rot3,0.0,1.0,0.0);
				glutSolidTorus(2.0, 4.0, 2.0, 30.0);
			glPopMatrix();
			x_o += 20;
		}
		if(torus4 != NULL) {
			glPushMatrix();
				GLfloat color2[4] = {1.0, 1.0, 1.0, 1.0};
				glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
				glTranslatef(x_o, y_o, 0.0);
				glRotatef(rot4,0.0,1.0,0.0);
				glutSolidTorus(2.0, 4.0, 2.0, 30.0);
			glPopMatrix();
			x_o += 20;
		}
		glPopAttrib();
	}else if(debug_mode == TORPEDO){
		/*	LINE 10	*/
		int x_pos = -72;
		y_pos = 85;
		char string10[1024];
		char string10a[1024];
		for(int x = 0; x < 12; x++){
			if(torpedo_shot_and_alive[x]){
				sprintf_s(string10, " Torpedo %d Rotate: %f", (x+1), torpedos[x]->get_Rotate_Angle());
				char* iterator10 = string10;
				x_pos = -72;
				y_pos -= 10;
				while(*(iterator10) != '\0'){
					glRasterPos2f(x_pos, y_pos);
					glutBitmapCharacter((void*)font, *(iterator10));
					x_pos += 4;
					iterator10++;
				}
				//*	USED TO PRINT OUT NORMAL VECTORS
				sprintf_s(string10a, "<%.4f,%.4f,%.4f>", torpedos[x]->get_X_Norm(),torpedos[x]->get_Y_Norm(),torpedos[x]->get_Z_Norm());
				char* iterator10a = string10a;
				x_pos = -70;
				y_pos -= 10;
				while(*(iterator10a) != '\0'){
					glRasterPos2f(x_pos, y_pos);
					glutBitmapCharacter((void*)font, *(iterator10a));
					x_pos += 4;
					iterator10a++;
				}
			}
		}
	}
}