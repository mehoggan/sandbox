/*
 * mainwindow.h
 *
 *  Created on: Jul 27, 2009
 *      Author: Matthew
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "Armies.h"
#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QToolBar>
#include <QMenuBar>
#include <QAction>
#include <QLineEdit>
#include <QTextEdit>
#include <QFrame>
#include <QComboBox>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QCheckBox>
#include <QDockWidget>
#include "armylistcontainer.h"
#include "maindialog.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();

public slots:
	void setArmyChoice();
	void selectUnitType();

	void newFile();
	void saveFile();
	void editFile();
	void editUnit();
	void removeUnit();

	void setUpEnvironment();

private:
	void establishArmy();
	void setArmyString(QString);
	void setUnitString(QString);
	void setUpActions();
	void setPointValue(int);
	QString buildQuery(QString);
	QString processQuery(QString);
	QString modifyDescription(QString*);
	void checkNullsScrollAreas();

	ArmyListContainer* army_vector;
	MainDialog* m_dialog;
	int army_choice;
	int point_value;
	QString* army_string;
	QString* unit_string;

	QAction* actions[5];
	QToolBar* tool_bar;
	QMenuBar* menu_bar;
	QFrame* main_frame;
	QHBoxLayout* main_layout;
	QVBoxLayout* left_layout;

	QDockWidget* dock;
	QFrame* dock_frame;
	QLabel* unit_select_label;
	QComboBox* unit_select;
	QLabel* unit_name;
	QComboBox* unit_name_select;
	QScrollArea* _SA;
	QLabel* pts_label;
	QLineEdit* pts;
	QTextEdit* army_list;
	QHBoxLayout* right_inner_layout_top;
	QHBoxLayout* right_inner_layout_bottom;
	QVBoxLayout* dock_layout;
};

#endif /* MAINWINDOW_H_ */
