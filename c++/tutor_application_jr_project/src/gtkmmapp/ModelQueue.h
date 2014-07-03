/*
 * ModelQueue.h
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#ifndef MODELQUEUE_H_
#define MODELQUEUE_H_

#include "includes.h"
#include "Student.h"
#include "LinkedList.h"

class MainWindow;

class ModelQueue
{
public:
	ModelQueue();
	ModelQueue(MainWindow* hwnd);
	~ModelQueue();
	Student* get_Student(Glib::ustring full_Name);
	LinkedList<Student*>* get_Student_List();
	void add_Student(Student* stdnt);
	Student* get_Student(int index);
private:
	MainWindow* hwnd;
	int num_O_Students;
	LinkedList<Student*>* student_Queue;
};

#endif /* MODELQUEUE_H_ */
