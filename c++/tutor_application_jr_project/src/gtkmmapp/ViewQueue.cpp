/*
 * ViewQueue.cpp
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#include "ViewQueue.h"
#include "Student.h"

ViewQueue::ViewQueue()
{

}

ViewQueue::ViewQueue(MainWindow* hwnd)
{
	this->hwnd = hwnd;
	this->dialog = new Window();
	this->dialog->set_default_size(400, 300);
	this->dialog->set_border_width(1);
	this->dialog->set_title("Student Queue");

    //  Main Layout Widget
	this->main_layout = manage(new VBox());

	//	Create All Containers
	this->notebook_Frame = manage(new Frame());

	//	Build All Widgets
	this->notebook = manage(new Notebook());
	this->student_Window = manage(new ScrolledWindow);
	this->student_Window->set_policy(POLICY_NEVER, POLICY_ALWAYS);

	ustring tab1_label = "Student Queue";
	this->notebook->prepend_page(*(this->student_Window), tab1_label, false);

	this->m_ButtonBox = manage(new HButtonBox(BUTTONBOX_END, 1));
    this->m_Button_Quit = manage(new Button("Quit"));
	this->m_Button_Select = manage(new Button("Select"));

	//	Set Size Request
	this->notebook_Frame->set_size_request(-1, 300);

	//	Add Right Widgets to Containers
	this->m_ButtonBox->pack_end(*(this->m_Button_Select), false, false);
	this->m_ButtonBox->pack_end(*(this->m_Button_Quit), false, false);
	this->notebook_Frame->add(*(this->notebook));
	this->main_layout->pack_start(*(this->notebook_Frame), true, true);
	this->main_layout->pack_end(*(this->m_ButtonBox), true, true);
	this->dialog->add(*(this->main_layout));
}

ViewQueue::~ViewQueue()
{
}

void ViewQueue::set_Model(ModelQueue* mdl_Que)
{
	this->mdl_Que = mdl_Que;
}

Frame* ViewQueue::get_notebook_Frame()
{
	return this->notebook_Frame;
}

Notebook* ViewQueue::get_notebook()
{
	return this->notebook;
}

ScrolledWindow* ViewQueue::get_student_Window()
{
	return this->student_Window;
}

Window* ViewQueue::get_window()
{
	return this->dialog;
}

Button* ViewQueue::get_Quit_Button()
{
    return this->m_Button_Quit;
}

Button* ViewQueue::get_Select_Button()
{
    return this->m_Button_Select;
}

TreeView* ViewQueue::get_Tree_View()
{
    return this->m_TreeView;
}

TreeModel::Row& ViewQueue::get_Tree_Model_Row()
{
    return this->row;
}

Glib::RefPtr<Gtk::ListStore>& ViewQueue::get_List_Store()
{
    return this->m_refTreeModel;
}

ModelColumns* ViewQueue::get_Model_Columns()
{
    return this->m_Columns;
}

void ViewQueue::complete_GUI()
{
    this->m_Columns = new ModelColumns();
    this->m_TreeView = manage(new TreeView());
    this->student_Window->add(*(this->m_TreeView));


    this->m_refTreeModel = ListStore::create(*(this->m_Columns));
    this->m_TreeView->set_model(this->m_refTreeModel);


	Student* student;
	int place = 0;
	while((student = this->mdl_Que->get_Student(place)) != NULL)
	{
        row = *(m_refTreeModel->append());

        row[m_Columns->m_col_id] = place + 1;

	    Glib::ustring name = student->get_first_Name().append(" ");
	    name.append(student->get_last_Name());
	    row[m_Columns->m_col_name] = name;

	    row[m_Columns->m_col_subject] = student->get_subject_Name();

	    place++;
	}

	//Add the TreeView's view columns:
	//This number will be shown with the default numeric formatting.
	m_TreeView->append_column("ID", m_Columns->m_col_id);
	m_TreeView->append_column("Name", m_Columns->m_col_name);
	m_TreeView->append_column("Subject", m_Columns->m_col_subject);

    //Display a progress bar instead of a decimal number:
	CellRendererProgress* cell = manage(new Gtk::CellRendererProgress);
	int cols_count = m_TreeView->append_column("Time Waited", *cell);
	//row[m_Columns.m_col_time] = 15;
	TreeViewColumn* pColumn = m_TreeView->get_column(cols_count - 1);
	if(pColumn)
	{
		pColumn->add_attribute(*cell, "value", m_Columns->m_col_time);
	}

	this->dialog->show_all_children();
}































