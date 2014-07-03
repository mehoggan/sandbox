#include "Student.h"

Student::Student(Glib::ustring first_Name, Glib::ustring last_Name, Glib::ustring subject, Glib::ustring time_in_queue)
{
    this->first_Name = first_Name;
    this->last_Name = last_Name;
    this->subject = subject;
    this->time_in_queue = time_in_queue;
}

Student::~Student()
{

}

Glib::ustring Student::get_first_Name()
{
    return this->first_Name;
}

Glib::ustring Student::get_last_Name()
{
    return this->last_Name;
}

Glib::ustring Student::get_subject_Name()
{
    return this->subject;
}

Glib::ustring Student::get_time_in_queue()
{
    return this->time_in_queue;
}
