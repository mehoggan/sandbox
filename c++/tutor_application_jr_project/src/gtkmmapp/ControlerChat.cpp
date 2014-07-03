/*
 * ControlerChat.cpp
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#include "ControlerChat.h"
#include "MainWindow.h"

ControlerChat::ControlerChat()
{

}

ControlerChat::ControlerChat(MainWindow* hwnd, ModelChat* mdl_Chat, ViewChat* view_Chat)
{
	this->hwnd = hwnd;
	this->mdl_Chat = mdl_Chat;
	this->view_Chat = view_Chat;
	this->view_Chat->set_Model(this->mdl_Chat);
	this->Set_Sensitive_ALL(false);
	this->Set_Editable_ALL(false);
	this->view_Chat->get_student_Queue_Button()->signal_clicked().connect(sigc::mem_fun(*this, &ControlerChat::open_StudentQueue));
	this->view_Chat->get_log_Off_Button()->signal_clicked().connect(sigc::mem_fun(*this, &ControlerChat::terminate_Program));
	this->view_Chat->get_log_On_Button()->signal_clicked().connect(sigc::mem_fun(*this, &ControlerChat::open_Login));
	this->view_Chat->get_Input()->signal_realize().connect(sigc::mem_fun(*this, &ControlerChat::on_realize_create));
}

ControlerChat::~ControlerChat()
{

}

void ControlerChat::Set_Sensitive_ALL(bool active)
{
    //this->Set_Sensitive_Queue_Button(active);
	//this->Set_Sensitive_log_On(active);
	this->Set_Sensitive_log_Off(active);
    this->Set_Sensitive_fontclr_Option(active);
    this->Set_Sensitive_emo_Option(active);
}

void ControlerChat::Set_Editable_ALL(bool edit)
{
    this->Set_Editable_Output(edit);
    this->Set_Editable_Input(edit);
}

void ControlerChat::Set_Sensitive_Queue_Button(bool active)
{
    this->view_Chat->get_student_Queue_Button()->set_sensitive(active);
}

void ControlerChat::Set_Sensitive_log_On(bool active)
{
    this->view_Chat->get_log_On_Button()->set_sensitive(active);
}

void ControlerChat::Set_Sensitive_log_Off(bool active)
{
    this->view_Chat->get_log_Off_Button()->set_sensitive(active);
}

void ControlerChat::Set_Sensitive_fontclr_Option(bool active)
{
    this->view_Chat->get_fontclr_Option()->set_sensitive(active);
}

void ControlerChat::Set_Sensitive_emo_Option(bool active)
{
    this->view_Chat->get_emo_Option()->set_sensitive(active);
}

void ControlerChat::Set_Editable_Output(bool edit)
{
    this->view_Chat->get_Input()->set_editable(edit);
}

void ControlerChat::Set_Editable_Input(bool edit)
{
    this->view_Chat->get_Output()->set_editable(edit);
}

void ControlerChat::open_StudentQueue()
{
    this->hwnd->get_cntrl_Chat()->Set_Sensitive_ALL(false);
    this->hwnd->get_cntrl_Chat()->Set_Editable_ALL(false);
    this->hwnd->get_cntrl_Draw()->Set_Sensitive_ALL(false);
    this->check_Student_Queue();
    if(this->hwnd->get_mdl_Chat()->get_chat_socket() != NULL)
    {
        this->hwnd->get_mdl_Chat()->get_chat_socket()->set_session(false);
    }
    this->hwnd->get_socket()->set_session(false);
    this->hwnd->create_Student_Queue();
}

void ControlerChat::terminate_Program()
{
    cout << "Terminating Program" << endl;
    this->hwnd->hide();
}

void ControlerChat::open_Login()
{
    if(this->hwnd->get_mdl_Chat()->get_chat_socket() != NULL)
    {
        this->hwnd->get_mdl_Chat()->get_chat_socket()->set_session(false);
    }
    this->hwnd->get_socket()->set_session(false);
    this->hwnd->get_cntrl_Chat()->Set_Sensitive_ALL(false);
    this->hwnd->get_cntrl_Chat()->Set_Editable_ALL(false);
    this->hwnd->get_cntrl_Draw()->Set_Sensitive_ALL(false);
    this->hwnd->create_Login_Screen();
    this->check_Student_Queue();
    this->hwnd->create_Student_Queue();
}

void ControlerChat::check_Student_Queue()
{
    if(this->hwnd->get_mdl_Que() == NULL)
    {
    }
    else
    {
        delete this->hwnd->get_mdl_Que();
    }

    if(this->hwnd->get_view_Que() == NULL)
    {
    }
    else
    {
        delete this->hwnd->get_view_Que();
    }

    if(this->hwnd->get_cntrl_Que() == NULL)
    {
    }
    else
    {
        delete this->hwnd->get_cntrl_Que();
    }
}

bool ControlerChat::on_expose_event(GdkEventExpose* event)
{
}

bool ControlerChat::button_press_event(GdkEventButton* event)
{
}

bool ControlerChat::button_release_event(GdkEventButton* event)
{
}

bool ControlerChat::motion_notify_event(GdkEventMotion* event)
{
}

void ControlerChat::on_realize_create()
{
    this->view_Chat->get_Input()->signal_key_press_event().connect(sigc::mem_fun(*this, &ControlerChat::key_press_event), false);
}

bool ControlerChat::key_press_event(GdkEventKey* event)
{
    bool ret;
    if(event->keyval ==  GDK_Return)
    {
        if(event->state == GDK_SHIFT_MASK)
        {
            ret = false;
        }
        else
        {
            Glib::RefPtr<TextBuffer> output = this->view_Chat->get_Input()->get_buffer();
            Glib::ustring tutor_Name = this->hwnd->get_Tutor()->get_uname();
            tutor_Name.append(": ");
            const Glib::ustring output_String = output->get_text(false);
            tutor_Name.append(output_String);
            tutor_Name.append("\n");
            string packet = output_String;
            const char* packet_send = packet.c_str();
            this->mdl_Chat->get_chat_socket()->send_text_packet(packet_send);
            const Glib::ustring tutor_Input = tutor_Name;
            Glib::RefPtr<TextBuffer> input = this->view_Chat->get_Output()->get_buffer();
            Glib::ustring input_String = input->get_text(false);
            input_String.append(tutor_Input);
            const Glib::ustring total_Chat = input_String;
            input->set_text(total_Chat);
            output->set_text("");
            ret = true;
        }
    }
    else
    {
        ret = false;
    }
    return ret;
}

void ControlerChat::clear_Input()
{
    Glib::RefPtr<TextBuffer> input = this->view_Chat->get_Output()->get_buffer();
    input->set_text("");
}

void ControlerChat::clear_Output()
{
    Glib::RefPtr<TextBuffer> output = this->view_Chat->get_Input()->get_buffer();
    output->set_text("");
}

void ControlerChat::establish_Socket()
{
    this->mdl_Chat->establish_Socket();
}

void ControlerChat::delete_Socket()
{
    this->mdl_Chat->delete_Socket();
}

























