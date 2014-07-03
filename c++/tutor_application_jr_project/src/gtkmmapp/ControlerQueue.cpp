/*
 * ControlerQueue.cpp
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#include "ControlerQueue.h"
#include "MainWindow.h"

ControlerQueue::ControlerQueue() {

}

ControlerQueue::ControlerQueue(MainWindow* hwnd, ModelQueue* mdl_Queue, ViewQueue* view_Queue) {
	this->hwnd = hwnd;
	this->mdl_Que = mdl_Queue;
	this->view_Que = view_Queue;
	this->view_Que->set_Model(this->mdl_Que);
}

ControlerQueue::~ControlerQueue() {
}

void ControlerQueue::get_Data_From_Server() {
	char* header = (char*)malloc(4);
	sprintf(header, "%d", 2, 4);
	this->hwnd->get_socket()->send_packet(header);
	const char* student_Queue_Data = (this->hwnd->get_socket()->receive_packet_student_queue());
	char* parse = const_cast<char*>(student_Queue_Data);
	const char* student_Que = "Matthew Hoggan Physicis 2:7:30 Andrew Hamilton Math 24:0:0 Alex David Selebesy 0:0:1 Vahe Margoussian Automata 2:10:23 Daniel Serry Math 2:10:23";
	//this->build_Student_Vector(parse);
	this->build_Student_Vector((char*)student_Que);
}

void ControlerQueue::build_Student_Vector(char* data) {
	string tokens(data);
	Tokenizer* t = new Tokenizer(tokens);
	while(t->hasMoreTokens()) {
		Glib::ustring* firstName = NULL;
		Glib::ustring* lastName = NULL;
		Glib::ustring* subject = NULL;
		Glib::ustring* time_in_Queue = NULL;
		if(t->hasMoreTokens()) {
			firstName = new Glib::ustring(t->nextToken());
		}
		if(t->hasMoreTokens()) {
			lastName = new Glib::ustring(t->nextToken());
		}
		if(t->hasMoreTokens()) {
			subject = new Glib::ustring(t->nextToken());
		}
		if(t->hasMoreTokens()) {
			time_in_Queue = new Glib::ustring(t->nextToken());
		}
		if(firstName != NULL && lastName != NULL && subject != NULL && time_in_Queue != NULL) {
			Student* std = new Student(*(firstName), *(lastName), *(subject), *(time_in_Queue));
			this->mdl_Que->add_Student(std);
			delete std;
		}
	}
	this->view_Que->complete_GUI();
	this->view_Que->get_Quit_Button()->signal_clicked().connect(sigc::mem_fun(*this, &ControlerQueue::cancel_Selected_Student));
	this->view_Que->get_Select_Button()->signal_clicked().connect(sigc::mem_fun(*this, &ControlerQueue::select_Selected_Student));
	delete t;
}

void ControlerQueue::cancel_Selected_Student() {
	this->view_Que->get_window()->hide();
	//this->hwnd->get_cntrl_Chat()->Set_Sensitive_Queue_Button(true);
	this->hwnd->get_cntrl_Chat()->Set_Sensitive_log_Off(true);
	//this->hwnd->get_cntrl_Chat()->Set_Sensitive_log_On(true);
	if(this->hwnd->get_mdl_Chat()->get_chat_socket() != NULL) {
		this->hwnd->get_mdl_Chat()->get_chat_socket()->set_session(false);
        	if(this->hwnd->get_chat_thread() != NULL) {
			//this->hwnd->join_chat_thread();
		}
	}
	this->hwnd->get_socket()->set_session(false);
	if(this->hwnd->get_draw_thread() != NULL) {
		//this->hwnd->join_draw_thread();
	}
	cout << "Threads removed" << endl;
}

void ControlerQueue::select_Selected_Student() {
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->view_Que->get_Tree_View()->get_selection();
	TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter) {
		cout << "Student Selected" << endl;
		TreeModel::Row row = *(iter);
		Glib::ustring uname = row[this->view_Que->get_Model_Columns()->m_col_name];
		std::string name(uname);
		Tokenizer* t = new Tokenizer(name);
		Glib::ustring firstName = t->getToken(1);
		Glib::ustring lastName = t->getToken(2);
		Glib::ustring usubject = row[this->view_Que->get_Model_Columns()->m_col_subject];
		Glib::ustring time("0");
		Student selected(firstName, lastName, usubject, time);
		this->hwnd->set_Student(&selected);
		this->view_Que->get_window()->hide();
		string Name = t->getToken(1).append(" ");
		Name = Name.append(t->getToken(2));
		char* send = &Name[0];
		char packet[] = "3";
		this->hwnd->get_socket()->send_packet(packet);
		this->hwnd->get_socket()->send_packet(send);
		const char* new_line = "\n";
		this->hwnd->get_socket()->send_packet((char*)new_line);
		delete t;
		this->view_Que->get_window()->hide();
		this->hwnd->get_cntrl_Chat()->Set_Sensitive_ALL(true);
		this->hwnd->get_cntrl_Chat()->Set_Editable_Output(true);
		this->hwnd->get_cntrl_Draw()->Set_Sensitive_ALL(true);
		this->hwnd->get_mdl_Draw()->delete_Grid(3280, 2048);
		this->hwnd->get_mdl_Draw()->initilize_Grid(3280, 2048);
		Gtk::Allocation allocation = this->hwnd->get_view_Draw()->get_sketchBoard()->get_allocation();
		int width = allocation.get_width();
		int height = allocation.get_height();
		Glib::RefPtr<Gdk::Window> window = this->hwnd->get_view_Draw()->get_sketchBoard()->get_window();
		Gdk::Rectangle rect(0, 0, width, height);
		window->invalidate_rect(rect, false);
		this->hwnd->get_cntrl_Chat()->clear_Input();
		this->hwnd->get_cntrl_Chat()->clear_Output();
		this->hwnd->get_mdl_Chat()->get_chat_socket()->set_session(true);
		this->hwnd->create_chat_thread();
		this->hwnd->get_socket()->set_session(true);
		this->hwnd->create_draw_thread();
	}
}

bool ControlerQueue::on_expose_event(GdkEventExpose* event) {
}

bool ControlerQueue::button_press_event(GdkEventButton* event) {
}

bool ControlerQueue::button_release_event(GdkEventButton* event) {
}

bool ControlerQueue::motion_notify_event(GdkEventMotion* event) {
}























