/*
 * explosion.cpp
 *
 *  Created on: Sep 16, 2010
 *      Author: Matthew Hoggan
 */

#include "explosion.h"

/*
 * Constructors and De-constructors
 */
explosion::explosion(){
}
explosion::explosion(GLfloat x, GLfloat y, GLfloat z){
	glPushMatrix();
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX, this->transMatrix);
	glPopMatrix();
	this->x = x;
	this->y = y;
	this->z = z;
	this->transMatrix[12]=this->x;
	this->transMatrix[13]=this->y;
	this->transMatrix[14]=this->z;
	
	this->opacity1_d=0.90;
	this->opacity1_a=0.50;
	this->opacity1_s=0.40;
	
	this->opacity2_d=0.90;
	this->opacity2_a=0.50;
	this->opacity2_s=0.40;
	
	this->opacity3_d=0.90;
	this->opacity3_a=0.50;
	this->opacity3_s=0.40;
	
	this->diffuse1[0]=1.00; this->diffuse1[1]=0.00; this->diffuse1[2]=0.00; this->diffuse1[3]=this->opacity1_d;
	this->diffuse2[0]=1.00; this->diffuse2[1]=0.00; this->diffuse2[2]=0.00; this->diffuse2[3]=this->opacity2_d;
	this->diffuse3[0]=1.00; this->diffuse3[1]=0.00; this->diffuse3[2]=0.00; this->diffuse3[3]=this->opacity3_d;
	
	this->ambient1[0]=1.00; this->ambient1[1]=0.00; this->ambient1[2]=0.00; this->ambient1[3]=this->opacity1_a;
	this->ambient2[0]=1.00; this->ambient2[1]=0.00; this->ambient2[2]=0.00; this->ambient2[3]=this->opacity2_a;
	this->ambient3[0]=1.00; this->ambient3[1]=0.00; this->ambient3[2]=0.00; this->ambient3[3]=this->opacity3_a;
	
	this->spectral1[0]=1.00; this->spectral1[1]=0.00; this->spectral1[2]=0.00; this->spectral1[3]=this->opacity1_s;
	this->spectral2[0]=1.00; this->spectral2[1]=0.00; this->spectral2[2]=0.00; this->spectral2[3]=this->opacity2_s;
	this->spectral3[0]=1.00; this->spectral3[1]=0.00; this->spectral3[2]=0.00; this->spectral3[3]=this->opacity3_s;
}
explosion::~explosion(){
}
void explosion::draw(GLfloat radius1,GLfloat radius2,GLfloat radius3){
	glEnable(GL_BLEND);
	glPushMatrix();
	if(radius1>=100){ 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse1);
		glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient1);
		glMaterialfv(GL_FRONT, GL_SPECULAR, this->spectral1);
		glTranslatef(this->x,this->y,this->z);
		glutSolidSphere(radius1, 90, 180);
		
		this->opacity1_d-=0.05;
		this->opacity1_a-=0.05;
		this->opacity1_s-=0.05;
		
		this->diffuse1[0]=1.00; this->diffuse1[1]+=0.05; this->diffuse1[2]=0.00; this->diffuse1[3]=this->opacity1_d;
		this->ambient1[0]=1.00; this->ambient1[1]=0.00; this->ambient1[2]=0.00; this->ambient1[3]=this->opacity1_a;
		this->spectral1[0]=1.00; this->spectral1[1]=0.00; this->spectral1[2]=0.00; this->spectral1[3]=this->opacity1_s;
	}
	glPopMatrix();
	glPushMatrix();
	if(radius2>=100){
		glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse2);
		glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient2);
		glMaterialfv(GL_FRONT, GL_SPECULAR, this->spectral2);
		glTranslatef(this->x,this->y,this->z);
		glutSolidSphere(radius1, 90, 180);
		
		this->opacity2_d-=0.90;
		this->opacity2_a-=0.50;
		this->opacity2_s-=0.40;
		
		this->diffuse2[0]=1.00; this->diffuse2[1]+=0.05; this->diffuse2[2]=0.00; this->diffuse2[3]=this->opacity2_d;
		this->ambient2[0]=1.00; this->ambient2[1]+=0.05; this->ambient2[2]=0.00; this->ambient2[3]=this->opacity2_a;
		this->spectral2[0]=1.00; this->spectral2[1]+=0.05; this->spectral2[2]=0.00; this->spectral2[3]=this->opacity2_s;
	}
	glPopMatrix();
	glPushMatrix();
	if(radius3>=100){
		glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse3);
		glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient3);
		glMaterialfv(GL_FRONT, GL_SPECULAR, this->spectral3);
		glTranslatef(this->x,this->y,this->z);
		glutSolidSphere(radius1, 90, 180);
		
		this->opacity3_d-=0.90;
		this->opacity3_a-=0.50;
		this->opacity3_s-=0.40;
		
		this->diffuse3[0]=1.00; this->diffuse3[1]+=0.05; this->diffuse3[2]=0.00; this->diffuse3[3]=this->opacity3_d;
		this->spectral2[0]=1.00; this->spectral2[1]+=0.05; this->spectral2[2]=0.00; this->spectral2[3]=this->opacity2_s;
		this->spectral3[0]=1.00; this->spectral3[1]+=0.05; this->spectral3[2]=0.00; this->spectral3[3]=this->opacity3_s;
	}
	glPopMatrix();
		
	glDisable(GL_BLEND);
}