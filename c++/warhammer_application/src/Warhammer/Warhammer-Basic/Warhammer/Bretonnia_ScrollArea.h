/*
 * Bretonnia_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef BRETONNIA_SCROLLAREA_H_
#define BRETONNIA_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Bretonnia_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Bretonnia_ScrollArea(QWidget *parent);
	~Bretonnia_ScrollArea();
};

#endif /* BRETONNIA_SCROLLAREA_H_ */
