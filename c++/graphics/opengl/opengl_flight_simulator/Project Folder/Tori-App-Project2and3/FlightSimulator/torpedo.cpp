/*
 * torpedo.cpp
 *
 *  Created on: Sep 16, 2010
 *      Author: Matthew Hoggan
 */

#include "torpedo.h"
#include "torus.h"

/*
 *	Constant Variables
 */
const GLdouble PI = 3.14159265358979323846264338;

torpedo::torpedo(){

}
torpedo::torpedo(	double radius, double stacks, double slices, double red, double green, double blue,
					double x_o, double y_o, double z_o, double x_right, double y_right, double z_right,
					double x_up, double y_up, double z_up, double x_at, double y_at, double z_at, torus* target){

	this->target = target;
	this->radius = radius;
	this->stacks = stacks;
	this->slices = slices;
	this->color[0] = red;
	this->color[1] = green;
	this->color[2] = blue;

	this->rotateMatrix[0] = x_right;
	this->rotateMatrix[1] = y_right;
	this->rotateMatrix[2] = z_right;
	this->rotateMatrix[3] = 0.0;

	this->rotateMatrix[4] = x_up;
	this->rotateMatrix[5] = y_up;
	this->rotateMatrix[6] = z_up;
	this->rotateMatrix[7] = 0.0;

	this->rotateMatrix[8] = x_at; 
	this->rotateMatrix[9] = y_at;  
	this->rotateMatrix[10] = z_at;
	this->rotateMatrix[11] = 0.0;

	this->rotateMatrix[12] = 0.0;
	this->rotateMatrix[13] = 0.0;
	this->rotateMatrix[14] = 0.0;
	this->rotateMatrix[15] = 1.0;

	this->Matrix[0] = 1.0;
	this->Matrix[1] = 0.0;
	this->Matrix[2] = 0.0;
	this->Matrix[3] = 0.0;

	this->Matrix[4] = 0.0;
	this->Matrix[5] = 1.0;
	this->Matrix[6] = 0.0;
	this->Matrix[7] = 0.0;

	this->Matrix[8] = 0.0; 
	this->Matrix[9] = 0.0;  
	this->Matrix[10] = 1.0;
	this->Matrix[11] = 0.0;

	this->Matrix[12] = x_o;
	this->Matrix[13] = y_o;
	this->Matrix[14] = z_o;
	this->Matrix[15] = 1.0;
}
torpedo::~torpedo(){
}
void torpedo::draw(){
	//*
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, this->color); 
		glMultMatrixf(this->Matrix);											//	Move the torpedo based on its matrix	//		
		glMultMatrixf(this->rotateMatrix);
		//glutSolidCone(this->radius, 200, this->stacks, this->slices);				//	Draw the torpedo	//
		glutSolidSphere(this->radius, 20, 40);
	glPopMatrix();
	//*	DEBUG CODE FOR TORPEDOS
	glPushMatrix();
		/*
		glBegin(GL_LINES);	//	NORMAL VECTOR OF PLANE OF SHIPS AT VECTOR AND ITS TARGET
			glLineWidth(0.0005);
			GLfloat normal_color[4] = {0.0, 0.0, 1.0, 1.0};
			glMaterialfv(GL_FRONT, GL_DIFFUSE, normal_color); 
			glNormal3f(1.0, 1.0, 1.0);
			glVertex3f(this->get_X_Pos(), this->get_Y_Pos(), this->get_Z_Pos());
			glNormal3f(1.0, 1.0, 1.0);
			glVertex3f(	this->get_X_Pos()+this->normalToTarget[0]*500, 
						this->get_Y_Pos()+this->normalToTarget[1]*500, 
						this->get_Z_Pos()+this->normalToTarget[2]*500);
		glEnd();
		//*/
		/*
		glBegin(GL_LINES);	//	VECTOR TO TARGET
			glLineWidth(0.0005);
			GLfloat target_color[4] = {0.0, 1.0, 0.0, 1.0};
			glMaterialfv(GL_FRONT, GL_DIFFUSE, target_color); 
			glNormal3f(1.0, 1.0, 1.0);
			glVertex3f(this->get_X_Pos(), this->get_Y_Pos(), this->get_Z_Pos());
			glNormal3f(1.0, 1.0, 1.0);
			glVertex3f(	this->target->get_X_Pos(), 
						this->target->get_Y_Pos(), 
						this->target->get_Z_Pos());
		glEnd();
		//*/
		/*
		glBegin(GL_LINES);	//	AT VECTOR OF SHIP
			glLineWidth(0.0005);
			GLfloat at_color[4] = {1.0, 0.0, 0.0, 1.0};
			glMaterialfv(GL_FRONT, GL_DIFFUSE, at_color); 
			glNormal3f(1.0, 1.0, 1.0);
			glVertex3f(this->get_X_Pos(), this->get_Y_Pos(), this->get_Z_Pos());
			glNormal3f(1.0, 1.0, 1.0);
			glVertex3f(	this->get_X_Pos()+this->get_X_At()*500, 
						this->get_Y_Pos()+this->get_Y_At()*500, 
						this->get_Z_Pos()+this->get_Z_At()*500);
		glEnd();
		//*/
	glPopMatrix();
	//*/
}

/*
 *	These functions simply update the contents of the 
 *	torpedo's Matrix, mainly using glRotatef() and glTranslatef()
 */
void torpedo::turn(GLfloat angle, GLfloat x, GLfloat y, GLfloat z){
	glPushMatrix();
		glLoadMatrixf(this->rotateMatrix);
		glRotatef(angle, x, y, z);
		glGetFloatv(GL_MODELVIEW_MATRIX, this->rotateMatrix);
	glPopMatrix();
}

/*
 *	This function is for the homing missles
 */
void torpedo::seek_and_destroy(){
	//	OBTAIN THE VECTORS
	GLfloat V[3];	//	vector to target			V
	V[0] = this->get_Target()->get_X_Pos() - this->get_X_Pos();
	V[1] = this->get_Target()->get_Y_Pos() - this->get_Y_Pos();
	V[2] = this->get_Target()->get_Z_Pos() - this->get_Z_Pos();
	GLfloat U[3];	//	At vector of torpedo		U
	U[0] = this->get_X_At();
	U[1] = this->get_Y_At();
	U[2] = this->get_Z_At();
	this->cross_Product(V, U);
	this->rotateAngle = acos(this->dot_Product(V, U))*180/PI;
	if(this->rotateAngle > 5){
		this->turn(5, this->normalToTarget[0],  this->normalToTarget[1],  this->normalToTarget[2]);
	}else{
		this->turn(this->rotateAngle, this->normalToTarget[0],  this->normalToTarget[1],  this->normalToTarget[2]);
	}
	//*
	//	OBTAIN THE VECTORS AGAIN
	GLfloat V1[3];	//	vector to target			V
	V1[0] = this->get_Target()->get_X_Pos() - this->get_X_Pos();
	V1[1] = this->get_Target()->get_Y_Pos() - this->get_Y_Pos();
	V1[2] = this->get_Target()->get_Z_Pos() - this->get_Z_Pos();
	GLfloat U1[3];	//	At vector of torpedo		U
	U1[0] = this->get_X_At();
	U1[1] = this->get_Y_At();
	U1[2] = this->get_Z_At();
	this->cross_Product(V1, U1);
	GLfloat recompute = acos(this->dot_Product(V1, U1))*180/PI;
	if(recompute > this->rotateAngle && recompute > 5){
		this->turn(-10, this->normalToTarget[0],  this->normalToTarget[1],  this->normalToTarget[2]);
	}
	else if(recompute > this->rotateAngle && recompute <= 5){
		this->turn(-2*recompute, this->normalToTarget[0],  this->normalToTarget[1],  this->normalToTarget[2]);
	}
	//*/
}

void torpedo::cross_Product(GLfloat V[3], GLfloat U[3]){
	GLfloat mag_V = sqrt(pow((double)(V[0]), 2.0) + pow((double)(V[1]), 2.0) + pow((double)(V[2]), 2.0));
	V[0] /= mag_V;
	V[1] /= mag_V;
	V[2] /= mag_V;

	GLfloat mag_U = sqrt(pow((double)(U[0]), 2.0) + pow((double)(U[1]), 2.0) + pow((double)(U[2]), 2.0));
	U[0] /= mag_U;
	U[1] /= mag_U;
	U[2] /= mag_U;

	this->normalToTarget[0] = V[1]*U[2] - U[1]*V[2];
	this->normalToTarget[1] = V[2]*U[0] - V[0]*U[2];
	this->normalToTarget[2] = V[0]*U[1] - U[0]*V[1];
	GLfloat n_magnitude = sqrt(	pow((double)(this->normalToTarget[0]), 2.0) +
								pow((double)(this->normalToTarget[0]), 2.0) +
								pow((double)(this->normalToTarget[0]), 2.0));
	this->normalToTarget[0] /= n_magnitude;
	this->normalToTarget[1] /= n_magnitude;
	this->normalToTarget[2] /= n_magnitude;
}

GLfloat torpedo::dot_Product(GLfloat V[3], GLfloat U[3]){
	GLfloat v_dot_u = V[0]*U[0]+V[1]*U[1]+V[2]*U[2];
	return v_dot_u;
}
	
/*
 *	This function displays the contents of the ships Matrix
 */
void torpedo::Display_Matrix(char* operation, GLfloat matrix[16]){
	printf("%s\n", operation);
	printf("%10f ", matrix[0]);
	printf("%10f ", matrix[4]);
	printf("%10f ", matrix[8]);
	printf("%10f ", matrix[12]);
	printf("\n");

	printf("%10f ", matrix[1]);
	printf("%10f ", matrix[5]);
	printf("%10f ", matrix[9]);
	printf("%10f ", matrix[13]);
	printf("\n");

	printf("%10f ", matrix[2]);
	printf("%10f ", matrix[6]);
	printf("%10f ", matrix[10]);
	printf("%10f ", matrix[14]);
	printf("\n");

	printf("%10f ", matrix[3]);
	printf("%10f ", matrix[7]);
	printf("%10f ", matrix[11]);
	printf("%10f ", matrix[15]);
	printf("\n"); 
}
/*
 *	GET FOR TARGET
 */
torus* torpedo::get_Target(){
	return this->target;
}

void torpedo::set_Target(){
	this->target = NULL;
}

/*
 *	GET FOR RADIUS
 */
double torpedo::get_Radius(){
	return this->radius;
}

/*
 *	GET FOR ANGLE TO ROTATE
 */
GLfloat torpedo::get_Rotate_Angle(){
	return this->rotateAngle;
}

/*
 *	GET AND SET FOR THE COMPONENTS OF <RIGHT> VECTOR
 */
// Get and set for X component of <Right> Vector
GLfloat torpedo::get_X_Right(){
	return this->rotateMatrix[0];
}
void torpedo::set_X_Right(GLfloat x_right){
	this->rotateMatrix[0] = x_right;
}
// Get and set for Y component of <Right> Vector
GLfloat torpedo::get_Y_Right(){
	return this->rotateMatrix[1];
}
void torpedo::set_Y_Right(GLfloat y_right){
	this->rotateMatrix[1] = y_right;
}
// Get and set for Z component of <Right> Vector
GLfloat torpedo::get_Z_Right(){
	return this->rotateMatrix[2];
}
void torpedo::set_Z_Right(GLfloat z_right){
	this->rotateMatrix[2] = z_right;
}

/*
 *	GET AND SET FOR THE COMPONENTS OF <UP> VECTOR
 */
// Get and set for X component of <Up> Vector
GLfloat torpedo::get_X_Up(){
	return this->rotateMatrix[4];
}
void torpedo::set_X_Up(GLfloat x_up){
	this->rotateMatrix[4] = x_up;
}
// Get and set for Y component of <Up> Vector
GLfloat torpedo::get_Y_Up(){
	return this->rotateMatrix[5];
}
void torpedo::set_Y_Up(GLfloat y_up){
	this->rotateMatrix[5] = y_up;
}
// Get and set for Z component of <Up> Vector
GLfloat torpedo::get_Z_Up(){
	return this->rotateMatrix[6];
}
void torpedo::set_Z_Up(GLfloat z_up){
	this->rotateMatrix[6] = z_up;
}

/*
 *	GET AND SET FOR THE COMPONENTS OF <AT> VECTOR
 */
// Get and set for X component of <At> Vector
GLfloat torpedo::get_X_At(){
	return this->rotateMatrix[8];
}
void torpedo::set_X_At(GLfloat x_at){
	this->rotateMatrix[8] = x_at;
}
// Get and set for Y component of <At> Vector
GLfloat torpedo::get_Y_At(){
	return this->rotateMatrix[9];
}
void torpedo::set_Y_At(GLfloat y_at){
	this->rotateMatrix[9] = y_at;
}
// Get and set for Z component of <At> Vector
GLfloat torpedo::get_Z_At(){
	return this->rotateMatrix[10];
}
void torpedo::set_Z_At(GLfloat z_at){
	this->rotateMatrix[10] = z_at;
}

/*
 *	GET AND SET FOR THE COMPONENTS OF (POS POINT)
 */
// Get and set for X coordinate of (Pos)
GLfloat torpedo::get_X_Pos(){
	return this->Matrix[12];
}
void torpedo::set_X_Pos(GLfloat x_pos){
	this->Matrix[12] = x_pos;
}
// Get and set for Y coordinate of (Pos)
GLfloat torpedo::get_Y_Pos(){
	return this->Matrix[13];
}
void torpedo::set_Y_Pos(GLfloat y_pos){
	this->Matrix[13] = y_pos;
}
// Get and set for Z coordinate of (Pos)
GLfloat torpedo::get_Z_Pos(){
	return this->Matrix[14];
}
void torpedo::set_Z_Pos(GLfloat z_pos){
	this->Matrix[14] = z_pos;
}

// Get for the compoenents of normal vector
GLfloat torpedo::get_X_Norm(){
	return this->normalToTarget[0];
}

GLfloat torpedo::get_Y_Norm(){
	return this->normalToTarget[1];
}

GLfloat torpedo::get_Z_Norm(){
	return this->normalToTarget[2];
}

int torpedo::get_Angle_Direction(){
	return this->angleDirection;
}