/*
 * ModelQueue.cpp
 *
 *  Created on: Feb 14, 2010
 *      Author: Matthew
 */

#include "ModelQueue.h"

ModelQueue::ModelQueue()
{
}

ModelQueue::ModelQueue(MainWindow* hwnd)
{
	this->hwnd = hwnd;
	student_Queue = new LinkedList<Student*>();
}

ModelQueue::~ModelQueue()
{
    if(student_Queue == NULL)
    {
    }
    else
    {
        delete student_Queue;
    }
}

Student* ModelQueue::get_Student(Glib::ustring full_Name)
{
    Student* retn;
    return retn;
}

void ModelQueue::add_Student(Student* stdnt)
{
    Student* add = new Student(stdnt->get_first_Name(), stdnt->get_last_Name(), stdnt->get_subject_Name(), stdnt->get_time_in_queue());
    student_Queue->InsertTail(add);
    num_O_Students++;
}

Student* ModelQueue::get_Student(int index)
{
    Student* present_Student = student_Queue->getItem(index);
    return present_Student;
}

LinkedList<Student*>* ModelQueue::get_Student_List()
{
    return this->student_Queue;
}


















