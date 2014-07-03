/*
 * Lizardmen_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef LIZARDMEN_SCROLLAREA_H_
#define LIZARDMEN_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Lizardmen_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Lizardmen_ScrollArea(QWidget *parent);
	~Lizardmen_ScrollArea();
};

#endif /* LIZARDMEN_SCROLLAREA_H_ */
