/*
 * Tutor.cpp
 *
 *  Created on: Feb 7, 2010
 *      Author: Matthew Hoggan
 */

#include "Tutor.h"
Tutor::Tutor(Glib::ustring* uname, Glib::ustring* psswd)
{
	locale_from_utf8(*(uname));
	locale_from_utf8(*(psswd));

	this->uname = uname->c_str();
	this->psswd = psswd->c_str();
}

Tutor::~Tutor()
{
}

const char* Tutor::get_uname()
{
	return this->uname;
}

const char* Tutor::get_psswd()
{
	return this->psswd;
}

void Tutor::set_uname(char* uname)
{
	this->uname = uname;
}

void Tutor::set_psswd(char* pswd)
{
	this->psswd = psswd;
}
