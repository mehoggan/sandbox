/*
 * skybox.cpp
 *
 *  Created on: Sep 16, 2010
 *      Author: Matthew Hoggan
 */

#include "skybox.h"

/*
 * Constructors and De-constructors
 */
skybox::skybox(){
}
skybox::skybox(int size_of_box){
	this->size=size_of_box;
	int width=512;
	int height=512;
	this->data1=(unsigned char*)malloc(width*height*3);
	int readResult;
	
	file1=fopen("StarFieldCrap.raw", "r");
	readResult= fread(data1, width*height*3,1,file1);
	fclose(this->file1);
	

	//*
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, data1);
	free(data1);
	//*/
}
skybox::~skybox(){
}
void skybox::draw(){
	//*
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
		
	glDisable(GL_LIGHTING);

	//left
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);	glVertex3f(-size,-size,-size);
		glTexCoord2f(0,0);	glVertex3f(-size,-size,size);
		glTexCoord2f(1,0);	glVertex3f(-size,size,size);
		glTexCoord2f(1,1);	glVertex3f(-size,size,-size);
	glEnd();
		
		
	//right
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);  glVertex3f(size,-size,-size);
		glTexCoord2f(0,0);  glVertex3f(size,-size,size);
		glTexCoord2f(1,0);  glVertex3f(size,size,size);
		glTexCoord2f(1,1);  glVertex3f(size,size,-size);
	glEnd();

	//bottom
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);  glVertex3f(-size,-size,-size);
		glTexCoord2f(0,0);  glVertex3f(-size,-size,size);
		glTexCoord2f(1,0);  glVertex3f(size,-size,size);
		glTexCoord2f(1,1);  glVertex3f(size,-size,-size);
	glEnd();

		//top
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);  glVertex3f(-size,size,-size);
		glTexCoord2f(0,0);  glVertex3f(-size,size,size);
		glTexCoord2f(1,0);  glVertex3f(size,size,size);
		glTexCoord2f(1,1);  glVertex3f(size,size,-size);
	glEnd();
		

		//right
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);  glVertex3f(-size,-size,-size);
		glTexCoord2f(0,0);  glVertex3f(-size,size,-size);
		glTexCoord2f(1,0);  glVertex3f(size,size,-size);
		glTexCoord2f(1,1);  glVertex3f(size,-size,-size);
	glEnd();

	//left
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);  glVertex3f(-size,-size,size);
		glTexCoord2f(0,0);  glVertex3f(-size,size,size);
		glTexCoord2f(1,0);  glVertex3f(size,size,size);
		glTexCoord2f(1,1);  glVertex3f(size,-size,size);
	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	//*/
}