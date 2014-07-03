/*
 * ControlerChat.h
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#ifndef CONTROLERCHAT_H_
#define CONTROLERCHAT_H_

#include "includes.h"
#include "Controler.h"
#include "ModelChat.h"
#include "ViewChat.h"

class MainWindow;

class ControlerChat : public Controler
{
public:
	ControlerChat();
	ControlerChat(MainWindow* hwnd, ModelChat* mdl_Chat, ViewChat* view_Chat);
	~ControlerChat();

	void Set_Sensitive_ALL(bool active);
	void Set_Sensitive_Queue_Button(bool active);
	void Set_Sensitive_log_On(bool active);
	void Set_Sensitive_log_Off(bool active);
    void Set_Sensitive_fontclr_Option(bool active);
    void Set_Sensitive_emo_Option(bool active);

    void Set_Editable_ALL(bool edit);
	void Set_Editable_Output(bool edit);
	void Set_Editable_Input(bool edit);

	bool on_expose_event(GdkEventExpose* event);
	bool button_press_event(GdkEventButton* event);
	bool button_release_event(GdkEventButton* event);
	bool motion_notify_event(GdkEventMotion* event);

	void on_realize_create();
	bool key_press_event(GdkEventKey* event);

	void clear_Input();
	void clear_Output();

	void establish_Socket();
	void delete_Socket();

private:
	ModelChat* mdl_Chat;
	ViewChat* view_Chat;
	MainWindow* hwnd;
	void open_StudentQueue();
	void terminate_Program();
	void open_Login();
	void check_Student_Queue();
};

#endif /* CONTROLERCHAT_H_ */
