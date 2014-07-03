/*
 * ModelDrawing.cpp
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#include "ModelDrawing.h"

ModelDrawing::ModelDrawing() {
    this->draw_mode = ARROW;
    this->set_trans(0.0);
    this->grid = NULL;
    this->grid_Rows = 0;
    this->grid_Col = 0;
}

ModelDrawing::ModelDrawing(MainWindow* hwnd) {
	this->hwnd = hwnd;
}

ModelDrawing::~ModelDrawing() {

}

int ModelDrawing::get_draw_mode() {
    return draw_mode;
}

int ModelDrawing::get_left_Click_x() {
    return this->left_Click_x;
}

int ModelDrawing::get_left_Click_y() {
    return this->left_Click_y;
}

void ModelDrawing::set_left_Click_x_y(int x, int y) {
    this->left_Click_x = x;
    this->left_Click_y = y;
}

double ModelDrawing::get_trans() { return this->trans; }
void ModelDrawing::set_trans(double trans) { this->trans = trans; }
double ModelDrawing::get_red() { return this->red; }
double ModelDrawing::get_green() { return this->green; }
double ModelDrawing::get_blue() { return this->blue; }
void ModelDrawing::set_red(double red) { this->red = red; }
void ModelDrawing::set_green(double green) { this->green = green; }
void ModelDrawing::set_blue(double blue) { this->blue = blue; }
void ModelDrawing::set_rgb(double red, double green, double blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void ModelDrawing::set_draw_mode(DRAWINGMODE draw_mode) {
    switch(draw_mode)     {
        case 0: {
            this->draw_mode = PENCIL;
            break;
        }
        case 1: {
            this->draw_mode = ERASER;
            break;
        }
        case 2: {
            this->draw_mode = RECTANGLE;
            break;
        }
        case 3: {
            this->draw_mode = POLYGON;
            break;
        }
        case 4: {
            this->draw_mode = ELLIPSE;
            break;
        }
        case 5: {
            this->draw_mode = LINE;
            break;
        }
        case 6: {
            this->draw_mode = ARROW;
            break;
        }
        default: {
            cout << "An error has occured" << endl;
            exit(0);
        }
    }
}

void ModelDrawing::initilize_Grid(int width, int height) {
    this->grid_Col = width;
    this->grid_Rows = height;
    grid = new LinkedList<Shape*>**[width];
    for(int x = 0; x < width; x++) {
        grid[x] = new LinkedList<Shape*>*[height];
        for(int y = 0; y < height; y++) {
            grid[x][y] = new LinkedList<Shape*>();
        }
    }
}

void ModelDrawing::delete_Grid(int width, int height) {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            delete(grid[x][y]); 
        }
        delete(grid[x]);
    }
    delete(grid);
}

Shape* ModelDrawing::get_Shape(int x, int y, int z) {
    Shape* shape = grid[x][y]->getItem(z);
    if(shape != NULL) {
    }
    return shape;
}

void ModelDrawing::insert_shape(Shape* shape) {
    int x = shape->get_x_0();
    int y = shape->get_y_0();
    if(x >= 0 && x < this->grid_Col && y >= 0 && y < this->grid_Rows) {
        this->grid[x][y]->InsertHead(shape);
        this->shape = (Shape_Type)shape->get_type();
    }
}

void ModelDrawing::print_grid() {
    int x;
    int y;
    int z = 0;
    for(x = 0; x < this->grid_Col; x++) {
        for(y = 0; y < this->grid_Rows; y++) {
            while(grid[x][y]->getItem(z) != NULL) {
                z++;
            }
            z = 0;
        }
    }
}














