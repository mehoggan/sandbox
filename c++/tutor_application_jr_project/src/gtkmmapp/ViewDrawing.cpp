/*
 * ViewDrawing.cpp
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#include "ViewDrawing.h"

ViewDrawing::ViewDrawing()
{

}

ViewDrawing::ViewDrawing(MainWindow* hwnd) {
    this->hwnd = hwnd;
    this->cursor = NULL;
    //	Create All Containers
    this->left_VBox = manage(new VBox());
    this->drawing_Frame = manage(new Frame());
    this->tool_DivideBox = manage(new HBox());
    this->tool_VBox = manage(new VBox());
    this->ltopbutton_Frame = manage(new Frame());
    this->toptool_Bar = manage(new Toolbar());
    this->clrbtn_Frame = manage(new Frame());
    this->clrbtn_Box = manage(new HBox());

    //	Add Child Containers to Parent Containers
    this->left_VBox->pack_start(*(this->drawing_Frame), true, true);
    this->left_VBox->pack_start(*(this->tool_DivideBox), false, false);
    this->tool_DivideBox->pack_start(*(this->tool_VBox), true, true);
    this->tool_DivideBox->pack_end(*(this->clrbtn_Frame), false, false);
    this->clrbtn_Frame->add(*(this->clrbtn_Box));
    this->tool_VBox->pack_start(*(this->ltopbutton_Frame), false, false);

    //	Place Tool Containers into Left Frames
    this->ltopbutton_Frame->add(*(this->toptool_Bar));

    //	Build All Widgets
    this->sketchBoard = manage(new DrawingArea());
    this->ellipse_Image = manage(new Image("../../data/Tools_Images/ellipse.jpg"));
    this->ellipse_ToolButton = manage(new ToolButton(*(this->ellipse_Image), ""));
    this->line_Image = manage(new Image("../../data/Tools_Images/line.jpg"));
    this->line_ToolButton = manage(new ToolButton(*(this->line_Image), ""));
    this->polygon_Image = manage(new Image("../../data/Tools_Images/polygon.jpg"));
    this->polygon_ToolButton = manage(new ToolButton(*(this->polygon_Image), ""));
    this->rectangle_Image = manage(new Image("../../data/Tools_Images/rectangle.jpg"));
    this->rectangle_ToolButton = manage(new ToolButton(*(this->rectangle_Image), ""));
    this->eraser_Image = manage(new Image("../../data/Tools_Images/eraser.jpg"));
    this->eraser_ToolButton = manage(new ToolButton(*(this->eraser_Image), ""));
    this->pencil_Image = manage(new Image("../../data/Tools_Images/pencil.jpg"));
    this->pencil_ToolButton = manage(new ToolButton(*(this->pencil_Image), ""));
    this->arrow_Image = manage(new Image("../../data/Tools_Images/arrow.jpg"));
    this->arrow_ToolButton = manage(new ToolButton(*(this->arrow_Image), ""));
    this->color_Button = manage(new ColorButton());
    this->clearSketchBoard = manage(new Button("Clear"));
    this->refresh = manage(new Button("Refresh"));

    //	Add Left Widgets to Containers
    this->drawing_Frame->add(*(this->sketchBoard));
    this->toptool_Bar->add(*(this->pencil_ToolButton));
    this->toptool_Bar->add(*(this->eraser_ToolButton));
    this->toptool_Bar->add(*(this->rectangle_ToolButton));
    this->toptool_Bar->add(*(this->polygon_ToolButton));
    this->toptool_Bar->add(*(this->ellipse_ToolButton));
    this->toptool_Bar->add(*(this->line_ToolButton));
    this->toptool_Bar->add(*(this->arrow_ToolButton));
    this->clrbtn_Box->pack_start(*(this->clearSketchBoard), true, true);
    this->clrbtn_Box->pack_start(*(this->refresh), true, true);
    this->clrbtn_Box->pack_start(*(this->color_Button), true, true);

    //	Set Default Size
    this->left_VBox->set_size_request(800, 600);
    this->clrbtn_Frame->set_size_request(250, 120);
    this->toptool_Bar->set_size_request(-1, 120);
}

ViewDrawing::~ViewDrawing() {

}

void ViewDrawing::set_Model(ModelDrawing* mdl_Draw) { this->mdl_Draw = mdl_Draw; }
DrawingArea* ViewDrawing::get_sketchBoard() { return this->sketchBoard; }
VBox* ViewDrawing::get_left_VBox() { return this->left_VBox; }
ToolButton* ViewDrawing::get_ellipse_ToolButton() { return this->ellipse_ToolButton; }
ToolButton* ViewDrawing::get_eraser_ToolButton() { return this->eraser_ToolButton; }
ToolButton* ViewDrawing::get_line_ToolButton() { return this->line_ToolButton; }
ToolButton* ViewDrawing::get_pencil_ToolButton() { return this->pencil_ToolButton; }
ToolButton* ViewDrawing::get_polygon_ToolButton() { return this->polygon_ToolButton; }
ToolButton* ViewDrawing::get_rectangle_ToolButton() { return this->rectangle_ToolButton; }
ToolButton* ViewDrawing::get_arrow_ToolButton() { return this->arrow_ToolButton; }
ColorButton* ViewDrawing::get_color_Button() { return this->color_Button; }
Button* ViewDrawing::get_refresh() { return this->refresh; }
Button* ViewDrawing::get_clearSketchBoard() { return this->clearSketchBoard; }
Gdk::Cursor* ViewDrawing::get_cursor() { return this->cursor; }
void ViewDrawing::create_cursor() { this->cursor = new Gdk::Cursor(); }
void ViewDrawing::create_cursor(Gdk::CursorType cursor_Type) { 
	delete this->cursor;     
	this->cursor = new Gdk::Cursor(cursor_Type);
}
























