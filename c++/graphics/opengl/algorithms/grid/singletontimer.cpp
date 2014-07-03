#include "singletontimer.h"

template<> Timer<20> *Timer<20>::_instance = NULL;
template<> Timer<100> *Timer<100>::_instance = NULL;

