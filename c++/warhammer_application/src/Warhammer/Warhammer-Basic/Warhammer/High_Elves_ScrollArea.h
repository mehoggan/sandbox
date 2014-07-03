/*
 * High_Elves_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef HIGH_ELVES_SCROLLAREA_H_
#define HIGH_ELVES_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class High_Elves_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	High_Elves_ScrollArea(QWidget *parent);
	~High_Elves_ScrollArea();
};

#endif /* HIGH_ELVES_SCROLLAREA_H_ */
