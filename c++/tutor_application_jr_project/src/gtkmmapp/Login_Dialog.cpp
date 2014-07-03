/*
 * Login_Dialog.cpp
 *
 *  Created on: Mar 2, 2010
 *      Author: Matthew
 */

#include "Login_Dialog.h"
#include "MainWindow.h" // <-- This is a temport fix, I hope it does not have side effects

Login_Dialog::Login_Dialog(int type, MainWindow* hwnd)
{
	this->hwnd = hwnd;
	this->set_default_size(100, 150);

	this->user_layout = new HBox();
	this->pswd_layout = new HBox();


	this->user_name = new Label("Username");
	this->user_entry = new Entry();
	this->pswd_user = new Label("Password");
	this->pswd_entry = new Entry();
	this->Ok = add_button("Ok", 1);
	this->Cancel = add_button("Cancel", 0);

	/*
	 *  This is purely for testing purposes
	 */
	Glib::ustring* text0 = new Glib::ustring("You are connected to: ");
	Glib::ustring* text1 = new Glib::ustring(text0->append(*hwnd->get_socket()->get_server_domainname_string()));
	this->label_value = text1;
	this->status_label = new Label(*(this->label_value), ALIGN_LEFT, ALIGN_LEFT, false);
	/*
	 *	End of testing
	 */


	this->Ok->set_size_request(74, -1);
	this->Cancel->set_size_request(74, -1);
	this->pswd_entry->property_visibility() = false;

	this->user_layout->pack_start(*(this->user_name), true, true);
	this->user_layout->pack_end(*(this->user_entry), true, true);
	this->pswd_layout->pack_start(*(this->pswd_user), true, true);
	this->pswd_layout->pack_end(*(this->pswd_entry), true, true);
	this->get_vbox()->pack_start(*(this->user_layout));
	this->get_vbox()->pack_end(*(this->status_label), true, true);
	this->get_vbox()->pack_end(*(this->pswd_layout));

	this->show_all();
}

Login_Dialog::~Login_Dialog()
{
}

void Login_Dialog::set_status_label(Glib::ustring label)
{
	this->status_label->set_label(label);
}

Glib::ustring Login_Dialog::get_uname()
{
	return this->user_entry->get_text();
}

Glib::ustring Login_Dialog::get_psswd()
{
	return this->pswd_entry->get_text();
}

void Login_Dialog::set_uname(Glib::ustring uname)
{
	this->user_entry->set_text(uname);
}

void Login_Dialog::set_psswd(Glib::ustring psswd)
{
	this->pswd_entry->set_text(psswd);
}

void Login_Dialog::hash_password(char* psswd)
{
	printf("Hashing Password\n");
	int x = 0;
	char s;
	while((s = *(psswd + x)) != '\0')
	{
		*(psswd + x) = hash_char(*(psswd + x++));
	}
}

char Login_Dialog::hash_char(char c)
{
	c = (char)(c + 12);
	c = (char)(c % 12);
	return c;
}


