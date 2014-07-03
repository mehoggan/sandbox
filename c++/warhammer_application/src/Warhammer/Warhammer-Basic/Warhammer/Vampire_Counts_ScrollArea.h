/*
 * Vampire_Counts_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef VAMPIRE_COUNTS_SCROLLAREA_H_
#define VAMPIRE_COUNTS_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Vampire_Counts_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Vampire_Counts_ScrollArea(QWidget *parent);
	~Vampire_Counts_ScrollArea();
};

#endif /* VAMPIRE_COUNTS_SCROLLAREA_H_ */
