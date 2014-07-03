/*
 * Tomb_Kings_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef TOMB_KINGS_SCROLLAREA_H_
#define TOMB_KINGS_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Tomb_Kings_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Tomb_Kings_ScrollArea(QWidget *parent);
	~Tomb_Kings_ScrollArea();
};

#endif /* TOMB_KINGS_SCROLLAREA_H_ */
