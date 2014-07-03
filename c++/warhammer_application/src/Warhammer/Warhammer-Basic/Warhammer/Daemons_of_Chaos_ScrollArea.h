/*
 * Daemons_of_Chaos_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef DAEMONS_OF_CHAOS_SCROLLAREA_H_
#define DAEMONS_OF_CHAOS_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Daemons_of_Chaos_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Daemons_of_Chaos_ScrollArea(QWidget *parent);
	~Daemons_of_Chaos_ScrollArea();
};

#endif /* DAEMONS_OF_CHAOS_SCROLLAREA_H_ */
