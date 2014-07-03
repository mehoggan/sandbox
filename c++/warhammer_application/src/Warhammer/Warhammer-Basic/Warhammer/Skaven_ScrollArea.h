/*
 * Skaven_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef SKAVEN_SCROLLAREA_H_
#define SKAVEN_SCROLLAREA_H_


#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Skaven_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Skaven_ScrollArea(QWidget *parent);
	~Skaven_ScrollArea();
};

#endif /* SKAVEN_SCROLLAREA_H_ */
