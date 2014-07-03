/*
 * MainWindow.h
 *
 *  Created on: Feb 7, 2010
 *      Author: Matthew
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "includes.h"

#include "ModelDrawing.h"
#include "ViewDrawing.h"
#include "ControlerDrawing.h"
#include "ModelChat.h"
#include "ViewChat.h"
#include "ControlerChat.h"
#include "ModelQueue.h"
#include "ViewQueue.h"
#include "ControlerQueue.h"
#include "Login_Dialog.h"
#include "TCP_IP_Socket.h"
#include "Tutor.h"
#include "Student.h"

#define VALID 1

class MainWindow : public Window
{
public:
	MainWindow(int type);
	~MainWindow();

	void on_menu_file_new_generic();
	void on_menu_file_quit();

	ModelDrawing* get_mdl_Draw();
	ViewDrawing* get_view_Draw();
	ControlerDrawing* get_cntrl_Draw();

	ModelChat* get_mdl_Chat();
	ViewChat* get_view_Chat();
	ControlerChat* get_cntrl_Chat();

	ModelQueue* get_mdl_Que();
	ViewQueue* get_view_Que();
	ControlerQueue* get_cntrl_Que();

	Glib::Thread* get_chat_thread();
	Glib::Thread* get_draw_thread();

	void create_chat_thread();
    void create_draw_thread();

    void join_chat_thread();
    void join_draw_thread();

	Label* get_status_label();
	void set_status_label(Glib::ustring label);

	TCP_IP_Socket* get_socket();
	int Login_Screen();

	void set_Student(Student* set_std);
	Student* get_Student();

	void set_Tutor(Tutor* set_tutor);
	Tutor* get_Tutor();

	void create_Student_Queue();
	void create_Login_Screen();

	void on_realize_create();

private:
	TCP_IP_Socket* socket;

	Widget* menu;
	RefPtr<Gtk::ActionGroup> m_refActionGroup;
	RefPtr<Gtk::UIManager> m_refUIManager;

	ModelDrawing* mdl_Draw;
	ViewDrawing* view_Draw;
	ControlerDrawing* cntrl_Draw;

	ModelChat* mdl_Chat;
	ViewChat* view_Chat;
	ControlerChat* cntrl_Chat;

	ModelQueue* mdl_Que;
	ViewQueue* view_Que;
	ControlerQueue* cntrl_Que;

	Frame* label_frame;
	Label* status_label;

	Login_Dialog* login;
	Tutor* tutor;
	Student* student;

    Glib::Thread* chat_thread;
    Glib::Thread* draw_thread;

protected:
	//Containers
	HBox* main_HBox;
	VBox* base_VBox;
};

#endif /* MAINWINDOW_H_ */
