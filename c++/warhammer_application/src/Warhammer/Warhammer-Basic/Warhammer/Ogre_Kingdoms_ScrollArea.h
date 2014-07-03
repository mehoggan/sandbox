/*
 * Ogre_Kingdoms_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef OGRE_KINGDOMS_SCROLLAREA_H_
#define OGRE_KINGDOMS_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Ogre_Kingdoms_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Ogre_Kingdoms_ScrollArea(QWidget *parent);
	~Ogre_Kingdoms_ScrollArea();
};

#endif /* OGRE_KINGDOMS_SCROLLAREA_H_ */
