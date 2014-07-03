/*
 * Orcs_n_Goblins_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef ORCS_N_GOBLINS_SCROLLAREA_H_
#define ORCS_N_GOBLINS_SCROLLAREA_H_

#include <QScrollArea>
#include <QVector>
#include <QLabel>
#include <QCheckBox>

class Orcs_n_Goblins_ScrollArea : public QScrollArea
{
	Q_OBJECT
private:
    QWidget *parent;
public:
	Orcs_n_Goblins_ScrollArea(QWidget *parent);
	~Orcs_n_Goblins_ScrollArea();
};

#endif /* ORCS_N_GOBLINS_SCROLLAREA_H_ */
