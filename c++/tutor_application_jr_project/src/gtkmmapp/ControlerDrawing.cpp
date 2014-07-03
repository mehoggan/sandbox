/*
 * ControllerDrawing.cpp
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#include "ControlerDrawing.h"
#include "MainWindow.h"
#include "Shape.h"
#include "Circle.h"
#include "Polygon.h"
#include "Line.h"
#include "Square.h"

ControlerDrawing::ControlerDrawing()
{

}

ControlerDrawing::ControlerDrawing(MainWindow* hwnd, ModelDrawing* mdl_Draw, ViewDrawing* view_Draw) {
    this->hwnd = hwnd;
    this->mdl_Draw = mdl_Draw;
    this->view_Draw = view_Draw;
    this->view_Draw->set_Model(this->mdl_Draw);
    this->mdl_Draw->set_draw_mode(6);
    this->view_Draw->get_pencil_ToolButton()->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ControlerDrawing::Set_Drawing_Mode), 0));
    this->view_Draw->get_eraser_ToolButton()->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ControlerDrawing::Set_Drawing_Mode), 1));
    this->view_Draw->get_rectangle_ToolButton()->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ControlerDrawing::Set_Drawing_Mode), 2));
    this->view_Draw->get_polygon_ToolButton()->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ControlerDrawing::Set_Drawing_Mode), 3));
    this->view_Draw->get_ellipse_ToolButton()->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ControlerDrawing::Set_Drawing_Mode), 4));
    this->view_Draw->get_line_ToolButton()->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ControlerDrawing::Set_Drawing_Mode), 5));
    this->view_Draw->get_arrow_ToolButton()->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ControlerDrawing::Set_Drawing_Mode), 6));
    this->view_Draw->get_refresh()->signal_clicked().connect(sigc::mem_fun(*this, &ControlerDrawing::refresh));
    this->view_Draw->get_clearSketchBoard()->signal_clicked().connect(sigc::mem_fun(*this, &ControlerDrawing::clear));
    this->view_Draw->get_sketchBoard()->signal_realize().connect(sigc::mem_fun(*this, &ControlerDrawing::on_realize_create));
    this->event_state = NORMAL;
    this->view_Draw->get_color_Button()->signal_damage_event().connect(sigc::mem_fun(*this, &ControlerDrawing::on_damage), false);
    this->view_Draw->get_color_Button()->signal_color_set().connect(sigc::mem_fun(*this, &ControlerDrawing::on_color_change));
}

ControlerDrawing::~ControlerDrawing() {

}

void ControlerDrawing::Set_Sensitive_ALL(bool active) {
    this->Set_Sensitive_sketchBoard(active);
    this->Set_Sensitive_ellipse_ToolButton(active);
    this->Set_Sensitive_eraser_ToolButton(active);
    this->Set_Sensitive_line_ToolButton(active);
    this->Set_Sensitive_pencil_ToolButton(active);
    this->Set_Sensitive_polygon_ToolButton(active);
    this->Set_Sensitive_rectangle_ToolButton(active);
    this->view_Draw->get_arrow_ToolButton()->set_sensitive(active);
    this->Set_Sensitive_color_Button(active);
    this->Set_Sensitive_refresh_Button(active);
    this->Set_Sensitive_clear_Button(active);
}

void ControlerDrawing::Set_Sensitive_sketchBoard(bool active) { this->view_Draw->get_sketchBoard()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_ellipse_ToolButton(bool active) { this->view_Draw->get_ellipse_ToolButton()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_eraser_ToolButton(bool active) { this->view_Draw->get_eraser_ToolButton()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_line_ToolButton(bool active) { this->view_Draw->get_line_ToolButton()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_pencil_ToolButton(bool active) { this->view_Draw->get_pencil_ToolButton()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_polygon_ToolButton(bool active) { this->view_Draw->get_polygon_ToolButton()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_rectangle_ToolButton(bool active) { this->view_Draw->get_rectangle_ToolButton()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_arrow_ToolButton(bool active) { this->view_Draw->get_arrow_ToolButton()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_color_Button(bool active) { this->view_Draw->get_color_Button()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_clear_Button(bool active) { this->view_Draw->get_clearSketchBoard()->set_sensitive(active); }
void ControlerDrawing::Set_Sensitive_refresh_Button(bool active) { this->view_Draw->get_refresh()->set_sensitive(active); }
int ControlerDrawing::get_event_state() { return this->event_state; }
void ControlerDrawing::Set_Drawing_Mode(DRAWINGMODE type) {
    this->mdl_Draw->set_draw_mode(type);
    switch(type)
    {
        case 0:
        {
            this->change_cursor(Gdk::PENCIL);
            break;
        }
        case 1:
        {
            this->change_cursor(Gdk::CIRCLE);
            break;
        }
        case 2:
        {
            this->change_cursor(Gdk::CROSSHAIR);
            break;
        }
        case 3:
        {
            this->change_cursor(Gdk::CROSSHAIR);
            break;
        }
        case 4:
        {
            this->change_cursor(Gdk::CROSSHAIR);
            break;
        }
        case 5:
        {
            this->change_cursor(Gdk::CROSSHAIR);
            break;
        }
        case 6:
        {
            this->change_cursor(Gdk::CROSSHAIR);
            break;
        }
        case 7:
        {
            this->change_cursor();
            break;
        }
        default:
        {
            exit(0);
        }
    }
}

void ControlerDrawing::set_dc_color(double red, double green, double blue)
{
    double dRed = red/65535;
    double dGreen = green/65535;
    double dBlue = blue/65535;
    this->dc->set_source_rgb(dRed, dGreen, dBlue);
}

void ControlerDrawing::set_dc_color(double red, double green, double blue, double trans)
{
    this->dc->set_source_rgba(red, green, blue, trans);
}

void ControlerDrawing::set_dc_line_width(int width)
{
    this->dc->set_line_width(width);
}

void ControlerDrawing::on_realize_create() {
    this->view_Draw->get_sketchBoard()->signal_expose_event().connect(sigc::mem_fun(*this, &ControlerDrawing::on_expose_event), false);
    this->view_Draw->get_sketchBoard()->signal_button_press_event().connect(sigc::mem_fun(*this, &ControlerDrawing::button_press_event), false);
    this->view_Draw->get_sketchBoard()->signal_button_release_event().connect(sigc::mem_fun(*this, &ControlerDrawing::button_release_event), false);
    this->view_Draw->get_sketchBoard()->signal_motion_notify_event().connect(sigc::mem_fun(*this, &ControlerDrawing::motion_notify_event), false);
    this->view_Draw->get_sketchBoard()->add_events(Gdk::ALL_EVENTS_MASK);
    int draw_mode = this->mdl_Draw->get_draw_mode();
    this->change_cursor();
    this->dc = this->view_Draw->get_sketchBoard()->get_window()->create_cairo_context();
    this->on_color_change();
    this->set_dc_line_width(1.0);
    this->set_dc_color(this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue(), 1);
    Gtk::Allocation allocation = this->view_Draw->get_sketchBoard()->get_allocation();
    int width = allocation.get_width();
    int height = allocation.get_height();
    this->mdl_Draw->initilize_Grid(3280, 2048);
    cout << "*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*Canvas Created*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*" << endl;
}

void ControlerDrawing::change_cursor() {
    this->view_Draw->create_cursor();
    Glib::RefPtr<Gdk::Window> window = this->view_Draw->get_sketchBoard()->get_window();
    window->set_cursor(*(this->view_Draw->get_cursor()));
}

void ControlerDrawing::change_cursor(Gdk::CursorType cursor_Type) {
    this->view_Draw->create_cursor(cursor_Type);
    Glib::RefPtr<Gdk::Window> window = this->view_Draw->get_sketchBoard()->get_window();
    window->set_cursor(*(this->view_Draw->get_cursor()));
}

void ControlerDrawing::on_color_change() {
    this->event_state = COLOR_SELECTION;
    Gdk::Color color = this->view_Draw->get_color_Button()->get_color();
    gushort red = color.get_red();
    gushort green = color.get_green();
    gushort blue = color.get_blue();
    double iRed = (double)red;
    double iGreen = (double)green;
    double iBlue = (double)blue;
    this->mdl_Draw->set_rgb(iRed/65535, iGreen/65535, iBlue/65535);
    this->set_dc_color(iRed, iGreen, iBlue);
    if(this->hwnd->get_Student() != NULL) {
        this->refresh();
    }
}

bool ControlerDrawing::on_damage(GdkEventExpose* event) {
}

bool ControlerDrawing::on_expose_event(GdkEventExpose* event) {
    Gtk::Allocation allocation = this->view_Draw->get_sketchBoard()->get_allocation();
    int width = allocation.get_width(); 
    int height = allocation.get_height();
    this->refresh_Grid(width, height);
}

bool ControlerDrawing::button_press_event(GdkEventButton* event) {
    int x;
    int y;
    if((event->button) == 1) {
        this->event_state = MOUSE_DOWN;
        if(this->hwnd->get_Student() != NULL) {
            if(this->mdl_Draw->get_draw_mode() == 0) {
                view_Draw->get_sketchBoard()->get_pointer(x, y);
                this->dc->move_to(x, y);
                this->mdl_Draw->set_left_Click_x_y(x, y);
            }
            if(this->mdl_Draw->get_draw_mode() == 1) {
            }
            if(this->mdl_Draw->get_draw_mode() == 2) {
                view_Draw->get_sketchBoard()->get_pointer(x, y);
                this->mdl_Draw->set_left_Click_x_y(x, y);
            }
            if(this->mdl_Draw->get_draw_mode() == 3) {
                view_Draw->get_sketchBoard()->get_pointer(x, y);
                this->mdl_Draw->set_left_Click_x_y(x, y);
            }
            if(this->mdl_Draw->get_draw_mode() == 4) {
                view_Draw->get_sketchBoard()->get_pointer(x, y);
                this->mdl_Draw->set_left_Click_x_y(x, y);
            }
            if(this->mdl_Draw->get_draw_mode() == 5) {
                view_Draw->get_sketchBoard()->get_pointer(x, y);
                this->dc->move_to(x, y);
                this->mdl_Draw->set_left_Click_x_y(x, y);
            }
        }
    }
}

bool ControlerDrawing::button_release_event(GdkEventButton* event)
{
    int x;
    int y;
    view_Draw->get_sketchBoard()->get_pointer(x, y);
    cout << " " << endl;
    if((event->button) == 1) {
        this->event_state = MOUSE_UP;
        if(this->hwnd->get_Student() != NULL) {
            if(this->mdl_Draw->get_draw_mode() == 0) {
                double x_0 = (double)this->mdl_Draw->get_left_Click_x();
                double y_0 = (double)this->mdl_Draw->get_left_Click_y();
                double theta = this->calculate_theta(x_0, y_0, x, y);
                double radius = this->calculate_radius(x_0, y_0, x, y);
                this->dc->line_to(x, y);
                this->dc->stroke();
                this->mdl_Draw->set_left_Click_x_y(x, y);
                Line* line = new Line(0, radius, theta, x_0, y_0, x, y, 1, this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue());
                this->hwnd->get_socket()->send_shape_packet(line);
                this->mdl_Draw->insert_shape(line);
            }
            if(this->mdl_Draw->get_draw_mode() == 1) {

            }
            if(this->mdl_Draw->get_draw_mode() == 2) {
                double x_0 = (double)this->mdl_Draw->get_left_Click_x();
                double y_0 = (double)this->mdl_Draw->get_left_Click_y();
                double theta = this->calculate_theta(x_0, y_0, x, y);
                double radius = this->calculate_radius(x_0, y_0, x, y);
                this->draw_polygon(x_0, y_0, 4, radius, theta, this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue());
                Square* square = new Square(1, radius, theta, x_0, y_0, x, y, 4, this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue());
                this->hwnd->get_socket()->send_shape_packet(square);
                this->mdl_Draw->insert_shape(square);
            }
            if(this->mdl_Draw->get_draw_mode() == 3) {
                double x_0 = (double)this->mdl_Draw->get_left_Click_x();
                double y_0 = (double)this->mdl_Draw->get_left_Click_y();
                double theta = this->calculate_theta(x_0, y_0, x, y);
                double radius = this->calculate_radius(x_0, y_0, x, y);
                int sides = 5;
                this->draw_polygon(x_0, y_0, sides, radius, theta, this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue());
                Polygon* polygon = new Polygon(2, radius, theta, x_0, y_0, x, y, sides, this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue());
                this->hwnd->get_socket()->send_shape_packet(polygon);
                this->mdl_Draw->insert_shape(polygon);
            } 
           if(this->mdl_Draw->get_draw_mode() == 4) {
                double x_0 = (double)this->mdl_Draw->get_left_Click_x();
                double y_0 = (double)this->mdl_Draw->get_left_Click_y();
                double theta = this->calculate_theta(x_0, y_0, x, y);
                double radius = this->calculate_radius(x_0, y_0, x, y);
                this->draw_circle(x_0, y_0, radius, this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue());
                Circle* circle = new Circle(3, radius, theta, x_0, y_0, x, y, -1, this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue());
                this->hwnd->get_socket()->send_shape_packet(circle);
                this->mdl_Draw->insert_shape(circle);
            }
            if(this->mdl_Draw->get_draw_mode() == 5) {
                double x_0 = (double)this->mdl_Draw->get_left_Click_x();
                double y_0 = (double)this->mdl_Draw->get_left_Click_y();
                double theta = this->calculate_theta(x_0, y_0, x, y);
                double radius = this->calculate_radius(x_0, y_0, x, y);
                this->dc->line_to(x, y);
                this->dc->stroke();
                this->mdl_Draw->set_left_Click_x_y(x, y);
                Line* line = new Line(0, radius, theta, x_0, y_0, x, y, 1, this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue());
                this->hwnd->get_socket()->send_shape_packet(line);
                this->mdl_Draw->insert_shape(line);
            }
        }
    }
}

bool ControlerDrawing::motion_notify_event(GdkEventMotion* event)
{
    int x;
    int y;
    view_Draw->get_sketchBoard()->get_pointer(x, y);
    if(this->hwnd->get_Student() != NULL) {
        if(this->event_state == MOUSE_DOWN) {
            if(this->mdl_Draw->get_draw_mode() == 0) {
                double x_0 = (double)this->mdl_Draw->get_left_Click_x();
                double y_0 = (double)this->mdl_Draw->get_left_Click_y();
                double theta = this->calculate_theta(x_0, y_0, x, y);
                double radius = this->calculate_radius(x_0, y_0, x, y);
                this->dc->line_to(x, y);
                this->dc->stroke();
                this->dc->move_to(x, y);
                this->mdl_Draw->set_left_Click_x_y(x, y);
                Line* line = new Line(0, radius, theta, x_0, y_0, x, y, 1, this->mdl_Draw->get_red(), this->mdl_Draw->get_green(), this->mdl_Draw->get_blue());
                cout << "Passing Socket a Line" << endl;
                //this->hwnd->get_socket()->send_shape_packet(line);
                this->mdl_Draw->insert_shape(line);
            }
	    if(this->mdl_Draw->get_draw_mode() == 1) {
                Glib::RefPtr<Gdk::Window> window = this->view_Draw->get_sketchBoard()->get_window();
                Gdk::Rectangle rect(x, y, 20, 20);
                window->invalidate_rect(rect, false);
            }
	}
    }
    char* status = (char*)malloc(256);
    sprintf(status, "(%d, %d)", x, y);
    Glib::ustring stat(status);
    this->hwnd->set_status_label(stat);
    free(status);
}

void ControlerDrawing::draw_polygon(double x_0, double y_0, int sides, double radius, double angle, double red, double green, double blue) {
    cout << "Drawing Polygon" << endl;
    double y_i = y_0 + radius * sin(angle);
    double x_i = x_0 + radius * cos(angle);
    this->dc->move_to(x_i, y_i);
    double delta_angle = ((2 * M_PI)/sides);
    for(int i = 2; i <= sides + 1; i++) {
        angle = angle + delta_angle;
        while(angle > 2 * M_PI) {
            angle = angle -2 * M_PI;
        }
        y_i = y_i + radius * sin(angle);
        x_i = x_i + radius * cos(angle);
        this->dc->line_to(x_i, y_i);
        this->dc->move_to(x_i, y_i);
    }
    this->dc->stroke();
}

void ControlerDrawing::draw_line(double x_0, double y_0, double x, double y, double red, double green, double blue) {
    cout << "Drawing Line" << endl;
    this->dc->move_to((int)x_0, (int)y_0);
    this->dc->line_to((int)x, (int)y);
    this->dc->stroke();
}

void ControlerDrawing::draw_circle(double x_0, double y_0, double radius, double red, double green, double blue) {
    cout << "Drawing Circle" << endl;
    this->dc->arc(x_0, y_0, radius, 0.0, 2.0 * M_PI);
    this->dc->stroke();
}

double ControlerDrawing::calculate_radius(int x_0, int y_0, int x, int y) {
    double delta_x_0 = (double)x - x_0;
    double delta_y_0 = (double)y - y_0;
    double radius = sqrt(pow(delta_x_0, 2.0) + pow(delta_y_0, 2.0));
    return radius;
}

void ControlerDrawing::refresh_Grid(int width, int height) {
    int z = 0;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            Shape* temp;
            while((temp = this->mdl_Draw->get_Shape(x, y, z)) != NULL) {
                this->dc->save();
                this->dc->set_source_rgb(temp->get_red(), temp->get_green(), temp->get_blue());
                if((int)temp->get_type() == 0) {
                    this->draw_line     (
                                            temp->get_x_0(), 
                                            temp->get_y_0(), 
                                            temp->get_x(), 
                                            temp->get_y(), 
                                            temp->get_red(), 
                                            temp->get_green(), 
                                            temp->get_blue()
                                        );
                }
                else if((int)temp->get_type() == 1) {
                    this->draw_polygon  (
                                            temp->get_x_0(), 
                                            temp->get_y_0(), 
                                            temp->get_sides(), 
                                            temp->get_radius(), 
                                            temp->get_theta(), 
                                            temp->get_red(), 
                                            temp->get_green(), 
                                            temp->get_blue()
                                        );
                }
                else if((int)temp->get_type() == 2) {
                    this->draw_polygon	(
                                            temp->get_x_0(), 
                                            temp->get_y_0(), 
                                            temp->get_sides(), 
                                            temp->get_radius(), 
                                            temp->get_theta(), 
                                            temp->get_red(), 
                                            temp->get_green(), 
                                            temp->get_blue()
                                        );
                }
                else if((int)temp->get_type() == 3) {
                    this->draw_circle   (
                                            temp->get_x_0(), 
                                            temp->get_y_0(), 
                                            temp->get_radius(), 
                                            temp->get_red(), 
                                            temp->get_green(), 
                                            temp->get_blue()
                                        );
                }
                z++;
        	this->dc->restore();
            }
            z = 0;
        }
    }
}

double ControlerDrawing::calculate_theta(int x_0, int y_0, int x, int y) {
    double delta_x_0 = (double)x - x_0;
    double delta_y_0 = (double)y - y_0;
    double theta = atan(delta_y_0 / delta_x_0);
    if(delta_x_0 < 0 && delta_y_0 < 0) {
        theta = theta + M_PI;
    }
    else if(delta_x_0 < 0) {
        theta = theta + (M_PI);
    }
    else if(delta_y_0 < 0) {
        theta = theta + 2 * M_PI;
    }
    else if(delta_x_0 == 0) {
        theta = 0;
    }
    return theta;
}

void ControlerDrawing::refresh() {
    Gtk::Allocation allocation = this->view_Draw->get_sketchBoard()->get_allocation();
    int width = allocation.get_width();
    int height = allocation.get_height();
    this->refresh_Grid(width, height);
}

void ControlerDrawing::clear() {
    this->mdl_Draw->delete_Grid(3280, 2048);
    this->mdl_Draw->initilize_Grid(3280, 2048);
    Gtk::Allocation allocation = this->view_Draw->get_sketchBoard()->get_allocation();
    int width = allocation.get_width();
    int height = allocation.get_height();
    Glib::RefPtr<Gdk::Window> window = this->view_Draw->get_sketchBoard()->get_window();
    Gdk::Rectangle rect(0, 0, width, height);
    window->invalidate_rect(rect, false);
}










