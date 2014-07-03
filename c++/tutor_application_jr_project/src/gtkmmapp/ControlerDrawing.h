/*
 * ControlerDrawing.h
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#ifndef CONTROLERDRAWING_H_
#define CONTROLERDRAWING_H_

#include "includes.h"
#include "Controler.h"
#include "ModelDrawing.h"
#include "ViewDrawing.h"
typedef int DRAWINGMODE;

class MainWindow;

class ControlerDrawing : public Controler
{
public:
	ControlerDrawing();
	ControlerDrawing(MainWindow* hwnd, ModelDrawing* mdl_Draw, ViewDrawing* view_Draw);
	~ControlerDrawing();

	void Set_Sensitive_ALL(bool active);
	void Set_Sensitive_sketchBoard(bool active);
	void Set_Sensitive_ellipse_ToolButton(bool active);
	void Set_Sensitive_eraser_ToolButton(bool active);
	void Set_Sensitive_text_ToolButton(bool active);
	void Set_Sensitive_line_ToolButton(bool active);
	void Set_Sensitive_pencil_ToolButton(bool active);
	void Set_Sensitive_polygon_ToolButton(bool active);
	void Set_Sensitive_rectangle_ToolButton(bool active);
	void Set_Sensitive_arrow_ToolButton(bool active);
	void Set_Sensitive_color_Button(bool active);
	void Set_Sensitive_clear_Button(bool active);
	void Set_Sensitive_refresh_Button(bool active);

	void change_cursor();
	void change_cursor(Gdk::CursorType cursor_Type);

	bool on_expose_event(GdkEventExpose* event);
	bool button_press_event(GdkEventButton* event);
	bool button_release_event(GdkEventButton* event);
	bool motion_notify_event(GdkEventMotion* event);
	bool on_damage(GdkEventExpose* event);

	int get_event_state();

private:
	ModelDrawing* mdl_Draw;
	ViewDrawing* view_Draw;
	MainWindow* hwnd;

	Cairo::RefPtr<Cairo::Context> dc;

    void Set_Drawing_Mode(DRAWINGMODE type);
    void on_realize_create();
    void on_color_change();

    void set_dc_color(double red, double green, double blue);
    void set_dc_color(double red, double green, double blue, double trans);
    void set_dc_line_width(int width);
    void refresh();
    void clear();

    enum Event_State
    {
        NORMAL, MOUSE_DOWN, MOUSE_UP, MOUSE_MOVE, COLOR_SELECTION, RESIZE
    } event_state;

    void draw_polygon(double x_0, double y_0, int sides, double radius, double angle, double red, double green, double blue);
    void draw_circle(double x_0, double y_0, double radius, double red, double green, double blue);
    void draw_line(double x_0, double y_0, double y, double x, double red, double green, double blue);
    double calculate_theta(int x_0, int y_0, int x, int y);
    double calculate_radius(int x_0, int y_0, int x, int y);
    void refresh_Grid(int width, int height);
};
#endif /* CONTROLERDRAWING_H_ */
