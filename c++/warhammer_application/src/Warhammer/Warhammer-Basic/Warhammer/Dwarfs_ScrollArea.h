/*
 * Dwarfs_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef DWARFS_SCROLLAREA_H_
#define DWARFS_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Dwarfs_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Dwarfs_ScrollArea(QWidget *parent);
	~Dwarfs_ScrollArea();
};

#endif /* DWARFS_SCROLLAREA_H_ */
