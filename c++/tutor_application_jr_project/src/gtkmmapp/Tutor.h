/*
 * Tutor.h
 *
 *  Created on: Feb 7, 2010
 *      Author: Matthew
 */

#include "includes.h"

class Tutor
{
public:
	Tutor(Glib::ustring* uname, Glib::ustring* psswd);
	~Tutor();
	const char* get_uname();
	const char* get_psswd();
	void set_uname(char* uname);
	void set_psswd(char* psswd);
private:
	const char* uname;
	const char* psswd;
};