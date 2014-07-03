/*
 * Controler.h
 *
 *  Created on: Feb 7, 2010
 *      Author: Matthew
 */

#ifndef CONTROLER_H_
#define CONTROLER_H_

#include "includes.h"

class Controler
{
public:
	Controler();
	virtual ~Controler();

    virtual bool on_expose_event(GdkEventExpose* event) = 0;
	virtual bool button_press_event(GdkEventButton* event) = 0;
	virtual bool button_release_event(GdkEventButton* event) = 0;
	virtual bool motion_notify_event(GdkEventMotion* event) = 0;
};

#endif
