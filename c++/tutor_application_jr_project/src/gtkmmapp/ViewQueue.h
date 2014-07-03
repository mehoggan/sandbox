/*
 * ViewQueue.h
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#ifndef VIEWQUEUE_H_
#define VIEWQUEUE_H_

#include "includes.h"
#include "Student.h"
#include "ModelQueue.h"
#include "ModelColumns.h"

class MainWindow;

class ViewQueue
{
protected:
	Frame* notebook_Frame;
	Notebook* notebook;
	ScrolledWindow* student_Window;
	HButtonBox* m_ButtonBox;
	Button* m_Button_Quit;
	Button* m_Button_Select;
    ModelColumns* m_Columns;
	Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
	TreeView* m_TreeView;
	TreeModel::Row row;
public:
	ViewQueue();
	ViewQueue(MainWindow* hwnd);
	~ViewQueue();
	void set_Model(ModelQueue* mdl_Que);
	Window* get_window();
	Frame* get_notebook_Frame();
	Notebook* get_notebook();
	ScrolledWindow* get_student_Window();
	Button* get_Quit_Button();
	Button* get_Select_Button();
	TreeView* get_Tree_View();
	TreeModel::Row& get_Tree_Model_Row();
	Glib::RefPtr<Gtk::ListStore>& get_List_Store();
	ModelColumns* get_Model_Columns();
    void complete_GUI();
    Student* get_Selected_Student();
private:
	MainWindow* hwnd;
	Window* dialog;
	VBox* main_layout;
	ModelQueue* mdl_Que;
};
#endif /* VIEWQUEUE_H_ */
