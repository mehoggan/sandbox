/*
 * DrawingView.h
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#ifndef DRAWINGVIEW_H_
#define DRAWINGVIEW_H_

#include "includes.h"

class MainWindow;
class ModelDrawing;

class ViewDrawing
{
public:
	ViewDrawing();
	ViewDrawing(MainWindow* hwnd);
	~ViewDrawing();
	void set_Model(ModelDrawing* mdl_Draw);
	VBox* get_left_VBox();

    DrawingArea* get_sketchBoard();
	ToolButton* get_ellipse_ToolButton();
	ToolButton* get_eraser_ToolButton();
	ToolButton* get_line_ToolButton();
	ToolButton* get_pencil_ToolButton();
	ToolButton* get_polygon_ToolButton();
	ToolButton* get_rectangle_ToolButton();
	ToolButton* get_arrow_ToolButton();
	ColorButton* get_color_Button();
	Button* get_clearSketchBoard();
	Button* get_refresh();

	Gdk::Cursor* get_cursor();
	void create_cursor();
	void create_cursor(Gdk::CursorType cursor_Type);

private:
	MainWindow* hwnd;
	ModelDrawing* mdl_Draw;
	Gdk::Cursor* cursor;

protected:
	VBox* left_VBox;
	Frame* drawing_Frame;
	HBox* tool_DivideBox;
	VBox* tool_VBox;
	Frame* ltopbutton_Frame;
	Toolbar* toptool_Bar;
	Frame* clrbtn_Frame;
	HBox* clrbtn_Box;

	DrawingArea* sketchBoard;
	Image* ellipse_Image;
	ToolButton* ellipse_ToolButton;
	Image* eraser_Image;
	ToolButton* eraser_ToolButton;
	Image* line_Image;
	ToolButton* line_ToolButton;
	Image* pencil_Image;
	ToolButton* pencil_ToolButton;
	Image* polygon_Image;
	ToolButton* polygon_ToolButton;
	Image* rectangle_Image;
	ToolButton* rectangle_ToolButton;
	Image* arrow_Image;
	ToolButton* arrow_ToolButton;
	Button* clearSketchBoard;
	Button* refresh;
	ColorButton* color_Button;
};

#endif /* DRAWINGVIEW_H_ */
