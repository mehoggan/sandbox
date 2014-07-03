/*
 * ControlerQueue.h
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#ifndef CONTROLERQUEUE_H_
#define CONTROLERQUEUE_H_

#include "includes.h"
#include "Controler.h"
#include "ModelQueue.h"
#include "ViewQueue.h"
#include "Tokenizer.h"

class MainWindow;

class ControlerQueue : public Controler
{
public:
	ControlerQueue();
	ControlerQueue(MainWindow* hwnd, ModelQueue* mdl_Que, ViewQueue* view_Que);
	~ControlerQueue();
	void get_Data_From_Server();
	void get_Selected_Student();
	void cancel_Selected_Student();
	void select_Selected_Student();
	void Show();

	bool on_expose_event(GdkEventExpose* event);
	bool button_press_event(GdkEventButton* event);
	bool button_release_event(GdkEventButton* event);
	bool motion_notify_event(GdkEventMotion* event);


private:
	ModelQueue* mdl_Que;
	ViewQueue* view_Que;
	MainWindow* hwnd;
	void build_Student_Vector(char* data);
};

#endif /* CONTROLERQUEUE_H_ */
