/*
 * The_Empire_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef THE_EMPIRE_SCROLLAREA_H_
#define THE_EMPIRE_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class The_Empire_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	The_Empire_ScrollArea(QWidget *parent);
	~The_Empire_ScrollArea();
};

#endif /* THE_EMPIRE_SCROLLAREA_H_ */
