/*
 * ViewChat.cpp
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#include "ViewChat.h"

ViewChat::ViewChat()
{

}

ViewChat::ViewChat(MainWindow* hwnd)
{
	//	Create All Containers
	this->right_VBox = manage(new VBox());
	this->output_Frame = manage(new Frame());
	this->rbutton_Frame = manage(new Frame());
	this->rbutton_HBox = manage(new HBox());
	this->input_Frame = manage(new Frame());
	this->text_VBox = manage(new VBox());
	this->text_Options = manage(new Toolbar());

	//	Add Child Containers to Parent Container
	this->right_VBox->pack_end(*(this->rbutton_Frame), false, false);
	this->right_VBox->pack_end(*(this->input_Frame), false, false);
	this->right_VBox->pack_end(*(this->output_Frame), true, true);
	this->text_VBox->pack_start(*(this->text_Options), true, true);

	//	Place Containers into Right Frames
	this->rbutton_Frame->add(*(this->rbutton_HBox));
	this->input_Frame->add(*(this->text_VBox));

	//	Build All Widgets
	this->scroll_Output = manage(new ScrolledWindow());
	this->Output = manage(new TextView());
	this->Output->set_border_window_size(TEXT_WINDOW_BOTTOM, 9);
	this->Output->set_wrap_mode (Gtk::WRAP_WORD_CHAR);
	this->scroll_Output->add(*(this->Output));
	this->scroll_Output->set_policy(POLICY_NEVER, POLICY_ALWAYS);
	this->Output->set_editable(false);
	this->student_Queue = manage(new Button("View Requests"));
	this->log_On = manage(new Button("Log In"));
	this->log_Off = manage(new Button("Log Out"));
	this->scroll_Input = manage(new ScrolledWindow());
	this->scroll_Input->set_policy(POLICY_NEVER, POLICY_ALWAYS);
	this->Input = manage(new TextView());
	this->Input->set_border_window_size(TEXT_WINDOW_TOP, 9);
	this->Input->set_wrap_mode (Gtk::WRAP_WORD_CHAR);
	this->scroll_Input->add(*(this->Input));
	this->font_Color = manage(new Image("./Tools_Images/fontcolor.png"));
	this->fontclr_Option = manage(new ToolButton(*(this->font_Color)));
	this->smily_Face = manage(new Image("./Tools_Images/smilyface.png"));
	this->emo_Option = manage(new ToolButton(*(this->smily_Face)));

	//	Set Size Request
	this->right_VBox->set_size_request(300, -1);
	this->output_Frame->set_size_request(300, 400);
	this->input_Frame->set_size_request(300, 200);
	this->text_Options->set_size_request(300, 10);
	this->Input->set_size_request(300, 30);
	this->rbutton_HBox->set_size_request(300,30);
	this->student_Queue->set_size_request(150, -1);
	this->log_On->set_size_request(74, -1);
	this->log_Off->set_size_request(74, -1);

	//	Add Right Widgets to Containers
	this->output_Frame->add(*(this->scroll_Output));
	this->rbutton_HBox->pack_start(*(this->student_Queue), false, false);
	this->rbutton_HBox->pack_start(*(this->log_On), false, false);
	this->rbutton_HBox->pack_start(*(this->log_Off), false, false);
	//this->text_Options->add(*(this->fontclr_Option));
	//this->text_Options->add(*(this->emo_Option));
	this->text_VBox->pack_end(*(this->scroll_Input), true, true);
}

ViewChat::~ViewChat()
{

}

void ViewChat::set_Model(ModelChat* mdl_Chat)
{
	this->mdl_Chat = mdl_Chat;
}

VBox* ViewChat::get_right_VBox()
{
	return (this->right_VBox);
}

Button* ViewChat::get_student_Queue_Button()
{
    return this->student_Queue;
}

Button* ViewChat::get_log_On_Button()
{
    return this->log_On;
}

Button* ViewChat::get_log_Off_Button()
{
    return this->log_Off;
}

ToolButton* ViewChat::get_fontclr_Option()
{
    return this->fontclr_Option;
}

ToolButton* ViewChat::get_emo_Option()
{
    return this->emo_Option;
}

TextView* ViewChat::get_Input()
{
    return this->Input;
}

TextView* ViewChat::get_Output()
{
    return this->Output;
}




















