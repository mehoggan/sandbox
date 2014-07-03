/*
 * Login_Dialog.h
 *
 *  Created on: Mar 2, 2010
 *      Author: Matthew
 */

#ifndef LOGIN_DIALOG_H_
#define LOGIN_DIALOG_H_

#include "includes.h"
class MainWindow;

class Login_Dialog : public Gtk::Dialog
{
public:
	Login_Dialog(int type, MainWindow* hwnd);
	~Login_Dialog();
	void set_status_label(Glib::ustring label);
	Glib::ustring get_uname();
	Glib::ustring get_psswd();
	void set_uname(Glib::ustring uname);
	void set_psswd(Glib::ustring psswd);
	void hash_password(char* psswd);

private:
	MainWindow* hwnd;
	Glib::ustring* label_value;
	char hash_char(char c);

protected:
	HBox* user_layout;
	HBox* pswd_layout;
	Label* user_name;
	Entry* user_entry;
	Label* pswd_user;
	Entry* pswd_entry;
	Button* Ok;
	Button* Cancel;
	Label* status_label;
};

#endif /* LOGIN_DIALOG_H_ */
