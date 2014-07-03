/*
 * Dark_Elves_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef DARK_ELVES_SCROLLAREA_H_
#define DARK_ELVES_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Dark_Elves_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Dark_Elves_ScrollArea(QWidget *parent);
	~Dark_Elves_ScrollArea();
};

#endif /* DARK_ELVES_SCROLLAREA_H_ */
