/*
 * camera.cpp
 *
 *  Created on: Sep 21, 2010
 *      Author: Matthew
 */

#include "camera.h"

camera::camera()
{

}

camera::~camera()
{

}

void camera::perspective(double angle, double aspect, double near_plane, double far_plane)
{
	gluPerspective(angle, aspect, near_plane, far_plane);
}

void camera::lookat(double eye_X, double eye_Y, double eye_Z, double at_X, double at_Y, double at_Z,
					double vector_X, double vector_Y, double vector_Z)
{
	gluLookAt(eye_X, eye_Y, eye_Z, at_X, at_Y, at_Z, vector_X, vector_Y, vector_Z);
}

double camera::get_angle()
{
	return this->angle;
}

double camera::get_aspect()
{
	return this->aspect;
}

double camera::get_near_plane()
{
	return this->near_plane;
}

double camera::get_far_plane()
{
	return this->far_plane;
}

double camera::get_eye_X()
{
	return this->eye_X;
}

double camera::get_eye_Y()
{
	return this->eye_Y;
}

double camera::get_eye_Z()
{
	return this->eye_Z;
}

double camera::get_at_X()
{
	return this->at_X;
}

double camera::get_at_Y()
{
	return this->at_Y;
}

double camera::get_at_Z()
{
	return this->at_Z;
}

double camera::get_vector_X()
{
	return this->vector_X;
}

double camera::get_vector_Y()
{
	return this->vector_Y;
}

double camera::get_vector_Z()
{
	return this->vector_Z;
}

void camera::set_angle(double angle)
{
	this->angle = angle;
}

void camera::set_aspect(double aspect)
{
	this->aspect = aspect;
}

void camera::set_near_plane(double near_plane)
{
	this->near_plane = near_plane;
}

void camera::set_far_plane(double far_plane)
{
	this->far_plane = far_plane;
}

void camera::set_eye_X(double eye_X)
{
	this->eye_X = eye_X;
}

void camera::set_eye_Y(double eye_Y)
{
	this->eye_Y = eye_Y;
}

void camera::set_eye_Z(double eye_Z)
{
	this->eye_Z = eye_Z;
}

void camera::set_at_X(double at_X)
{
	this->at_X = at_X;
}

void camera::set_at_Y(double at_Y)
{
	this->at_Y = at_Y;
}

void camera::set_at_Z(double at_Z)
{
	this->at_Z = at_Z;
}

void camera::set_vector_X(double vector_X)
{
	this->vector_X = vector_X;
}

void camera::set_vector_Y(double vector_Y)
{
	this->vector_Y = vector_Y;
}

void camera::set_vector_Z(double vector_Z)
{
	this->vector_Z = vector_Z;
}

