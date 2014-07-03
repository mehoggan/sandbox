/*
 * ModelDrawing.h
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#ifndef MODELDRAWING_H_
#define MODELDRAWING_H_

#include "includes.h"
#include "Shape.h"
#include "LinkedList.h"
typedef int DRAWINGMODE;

class MainWindow;

class ModelDrawing
{

private:
	MainWindow* hwnd;

	enum DrawingMode
	{
        PENCIL, ERASER, RECTANGLE, POLYGON, ELLIPSE, LINE, ARROW
	} draw_mode;

	int left_Click_x;
	int left_Click_y;

	double trans;

	double red;
	double blue;
    double green;

    LinkedList<Shape*>*** grid;
    int grid_Rows;
    int grid_Col;
public:
	ModelDrawing();
	ModelDrawing(MainWindow* hwnd);
	~ModelDrawing();

	int get_draw_mode();
	void set_draw_mode(DRAWINGMODE draw_mode);

	int get_left_Click_x();
	int get_left_Click_y();
    void set_left_Click_x_y(int x, int y);
    double get_trans();
    void set_trans(double trans);

    double get_red();
    double get_green();
    double get_blue();

    void set_red(double red);
    void set_green(double green);
    void set_blue(double blue);
    void set_rgb(double red, double green, double blue);
    void insert_shape(Shape* shape);

    enum Shape_Type
    {
        T_LINE, T_SQUARE, T_POLYGON, T_CIRCLE
    } shape;

    void initilize_Grid(int width, int height);
    void delete_Grid(int width, int height);
    Shape* get_Shape(int x, int y, int z);
    void print_grid();
};

#endif /* MODELDRAWING_H_ */
