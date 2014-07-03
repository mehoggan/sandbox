/*
 * Warriors_of_Chaos_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef WARRIORS_OF_CHAOS_SCROLLAREA_H_
#define WARRIORS_OF_CHAOS_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Warriors_of_Chaos_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Warriors_of_Chaos_ScrollArea(QWidget *parent);
	~Warriors_of_Chaos_ScrollArea();
};

#endif /* WARRIORS_OF_CHAOS_SCROLLAREA_H_ */
