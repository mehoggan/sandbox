/*
 * maindialog.h
 *
 *  Created on: Jul 27, 2009
 *      Author: Matthew
 */

#ifndef MAINDIALOG_H_
#define MAINDIALOG_H_

#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QPushButton>
#include <QDialog>
#include <QDesktopWidget>
#include "armylistcontainer.h"

class MainDialog : public QDialog
{
	Q_OBJECT
public:
	MainDialog(QWidget* parent);
	~MainDialog();
	int getArmyChoice();
	int getPointValue();

public slots:
	void YesArmyChoice();
	void NoArmyChoice();

private:
	void setArmyChoice(int);
	int army_choice;
	void setPointValue(int);
	int point_value;
	ArmyListContainer* vector_list;
	QComboBox* comboBox;
	QComboBox* pointBox;
	QPushButton* ok;
	QPushButton* cancel;
	QWidget* p_parent;
};

#endif /* MAINDIALOG_H_ */
