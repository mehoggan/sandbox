#ifndef STUDENT_H_
#define STUDENT_H_

#include "includes.h"

class Student
{
public:
    Student(Glib::ustring first_Name, Glib::ustring last_Name, Glib::ustring subject, Glib::ustring time_in_queue);
    ~Student();
    Glib::ustring get_first_Name();
    Glib::ustring get_last_Name();
    Glib::ustring get_subject_Name();
    Glib::ustring get_time_in_queue();
private:
    Glib::ustring first_Name;
    Glib::ustring last_Name;
    Glib::ustring subject;
    Glib::ustring time_in_queue;
};

#endif //STUDENT_H_
