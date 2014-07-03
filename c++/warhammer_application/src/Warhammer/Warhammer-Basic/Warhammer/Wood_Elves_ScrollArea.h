/*
 * Wood_Elves_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef WOOD_ELVES_SCROLLAREA_H_
#define WOOD_ELVES_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Wood_Elves_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Wood_Elves_ScrollArea(QWidget *parent);
	~Wood_Elves_ScrollArea();
};

#endif /* WOOD_ELVES_SCROLLAREA_H_ */
