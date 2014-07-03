/*
 * ViewChat.h
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#ifndef VIEWCHAT_H_
#define VIEWCHAT_H_

#include "includes.h"

class MainWindow;
class ModelChat;

class ViewChat
{
public:
	ViewChat();
	ViewChat(MainWindow* hwnd);
	~ViewChat();
	void set_Model(ModelChat* mdl_Chat);
	VBox* get_right_VBox();

	Button* get_student_Queue_Button();
	Button* get_log_On_Button();
	Button* get_log_Off_Button();
	ToolButton* get_fontclr_Option();
	ToolButton* get_emo_Option();
	TextView* get_Input();
	TextView* get_Output();

private:
	MainWindow* hwnd;
	ModelChat* mdl_Chat;

protected:
	VBox* right_VBox;
	Frame* output_Frame;
	Frame* rbutton_Frame;
	HBox* rbutton_HBox;
	Frame* input_Frame;
	VBox* text_VBox;
	Toolbar* text_Options;

	ScrolledWindow* scroll_Output;
	TextView* Output;
	Button* student_Queue;
	Button* log_On;
	Button* log_Off;
	Image* font_Color;
	ToolButton* fontclr_Option;
	Image* smily_Face;
	ToolButton* emo_Option;
	ScrolledWindow* scroll_Input;
	TextView* Input;
};

#endif /* VIEWCHAT_H_ */
