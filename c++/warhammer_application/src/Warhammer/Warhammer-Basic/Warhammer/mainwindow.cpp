/*
 * mainwindow.cpp
 *
 *  Created on: Jul 27, 2009
 *      Author: Matthew
 */
#include "Armies.h"
#include <iostream>
#include <string>
#include <fstream>
#include <QWidget>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QLineEdit>
#include <QFrame>
#include <QComboBox>
#include <QScrollArea>
#include <QTextEdit>
#include <QMessageBox>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QCheckBox>
#include <QSizePolicy>
#include "mainwindow.h"
#include "maindialog.h"
#include "armylistcontainer.h"

using namespace std;

MainWindow::MainWindow()
{
	dock = new QDockWidget(this);
	_SA = new QScrollArea(dock);

	m_dialog = new MainDialog(this);
	int option = m_dialog->exec();
	m_dialog->hide();
	int m_dialog_point_index = m_dialog->getPointValue();
	this->setPointValue(m_dialog_point_index);
	army_choice = m_dialog->getArmyChoice();

	menu_bar = new QMenuBar(this);
	this->setUpActions();
	QMenu* file = new QMenu(tr("&File"), this);
	menu_bar->addMenu(file);
	for(int x = 0; x < 3; x++)
	{
		file->addAction(actions[x]);
	}
	QMenu* edit = new QMenu(tr("&Edit"), this);
	menu_bar->addMenu(edit);
	for(int x = 3; x < 5; x++)
	{
		edit->addAction(actions[x]);
	}
	tool_bar = new QToolBar(this);
	for(int x = 0; x < 5; x++)
	{
		tool_bar->addAction(actions[x]);
	}
	this->setMenuBar(menu_bar);
	this->addToolBar(tool_bar);

	this->setMinimumSize(600,400);
	QDesktopWidget* desktop = new QDesktopWidget();
	int height = desktop->height();
	int width = desktop->width();
	this->setGeometry(0,0, width-100, height-100);
	this->setVisible(false);

	main_frame = new QFrame(this);
	dock_frame = new QFrame(dock);

	army_list = new QTextEdit(main_frame);
	army_list->setReadOnly(true);
	//army_list->setMinimumWidth(this->width()*(3/4));
	army_list->setMinimumWidth(700);

	unit_select_label = new QLabel("Choose Unit Type: ", dock_frame, 0);

	unit_select = new QComboBox(dock_frame);
	unit_select->addItem("Lords");
	unit_select->addItem("Heros");
	unit_select->addItem("Core");
	unit_select->addItem("Special");
	unit_select->addItem("Rare");
	unit_select->addItem("Special Characters");
	setUnitString(this->unit_select->currentText());
	connect(unit_select, SIGNAL(activated(int)), this, SLOT(selectUnitType()));

	unit_name = new QLabel(tr("Specific Unit"), dock_frame, 0);

	unit_name_select = new QComboBox(dock_frame);
	unit_name_select->setMinimumWidth(200);
	connect(unit_name_select, SIGNAL(activated(int)), this, SLOT(setUpEnvironment()));

	pts_label = new QLabel("Point Total: ", dock_frame);

	pts = new QLineEdit(dock_frame);
	pts->setReadOnly(true);
	pts->setText("0pts");

	main_layout = new QHBoxLayout();
	dock_layout = new QVBoxLayout();
	left_layout = new QVBoxLayout();
	right_inner_layout_top = new QHBoxLayout();
	right_inner_layout_bottom = new QHBoxLayout();

	main_layout->insertWidget(0, army_list, 0);
	this->setCentralWidget(army_list);
	main_frame->setLayout(main_layout);

	dock_layout->insertLayout(0, right_inner_layout_top, 0);
	right_inner_layout_top->insertWidget(0, unit_select_label, 0, 0);
	right_inner_layout_top->insertWidget(1, unit_select, 10, Qt::AlignLeft);
	right_inner_layout_top->insertWidget(2, unit_name, 0, 0);
	right_inner_layout_top->insertWidget(3, unit_name_select, 100, Qt::AlignLeft);
	dock_layout->insertWidget(1, _SA, 0);
	dock_layout->insertLayout(2, right_inner_layout_bottom, 0);
	right_inner_layout_bottom->addWidget(pts_label, 0, Qt::AlignRight);
	right_inner_layout_bottom->addWidget(pts, 1, Qt::AlignRight);
	dock_frame->setLayout(dock_layout);
	dock->setWidget(dock_frame);
	dock->setLayout(dock_layout);
	this->setCentralWidget(main_frame);
	this->addDockWidget(Qt::RightDockWidgetArea, dock);

	if(option == 1)
	{
		establishArmy();
		this->selectUnitType();
		cout << "Calling Establish Environment Function" << endl;
		setUpEnvironment();
	}

	this->show();
}

MainWindow::~MainWindow()
{
	delete _SA;
}

void MainWindow::setArmyString(QString string)
{
	army_string = new QString(string);
}

void MainWindow::setUnitString(QString string)
{
	unit_string = new QString(string);
}

void MainWindow::setArmyChoice()
{
	this->army_choice = m_dialog->getArmyChoice();
}

void MainWindow::establishArmy()
{
	if(army_choice != 0)
	{

		ArmyListContainer* choice = new ArmyListContainer();
		this->setArmyString(choice->vector->at(army_choice - 1));

		QString start = "You are going to build a:\n";
		QString number = QString::number(point_value, 10);
		number = number.append("pts ");
		QString complete = number.append(choice->vector->at(army_choice - 1));
		complete = complete.append(" Army");
		start = start.append(complete);
		delete choice;
	}
	else
	{
		this->setArmyString("");
	}
}

void MainWindow::setPointValue(int m_dialog_index)
{
	point_value = 0;
	if(m_dialog_index == 0)
	{
		point_value = 0;
	}
	else if(m_dialog_index == 1)
	{
		point_value = 500;
	}
	else if(m_dialog_index == 2)
	{
		point_value = 750;
	}
	else if(m_dialog_index == 3)
	{
		point_value = 1000;
	}
	else if(m_dialog_index == 4)
	{
		point_value = 1250;
	}
	else if(m_dialog_index == 5)
	{
		point_value = 1500;
	}
	else if(m_dialog_index == 6)
	{
		point_value = 1750;
	}
	else if(m_dialog_index == 7)
	{
		point_value = 2000;
	}
	else if(m_dialog_index == 8)
	{
		point_value = 2250;
	}
	else if(m_dialog_index == 9)
	{
		point_value = 2500;
	}
	else if(m_dialog_index == 10)
	{
		point_value = 2750;
	}
	else if(m_dialog_index == 11)
	{
		point_value = 3000;
	}
	else if(m_dialog_index == 12)
	{
		point_value = 3250;
	}
	else if(m_dialog_index == 13)
	{
		point_value = 3500;
	}
	else if(m_dialog_index == 14)
	{
		point_value = 3750;
	}
	else if(m_dialog_index == 15)
	{
		point_value = 4000;
	}
}

void MainWindow::setUpActions()
{
	this->actions[0] = new QAction(this);
	actions[0]->setText("New File");
	connect(actions[0], SIGNAL(triggered()), this, SLOT(newFile()));

	this->actions[1] = new QAction(this);
	actions[1]->setText("Save Flie");
	connect(actions[1], SIGNAL(triggered()), this, SLOT(saveFile()));

	this->actions[2] = new QAction(this);
	actions[2]->setText("Edit Flie");
	connect(actions[2], SIGNAL(triggered()), this, SLOT(editFile()));

	this->actions[3] = new QAction(this);
	actions[3]->setText("Edit Unit");
	connect(actions[3], SIGNAL(triggered()), this, SLOT(editUnit()));

	this->actions[4] = new QAction(this);
	actions[4]->setText("Remove Unit");
	connect(actions[4], SIGNAL(triggered()), this, SLOT(removeUnit()));
}

void MainWindow::newFile()
{
	this->setVisible(false);
	delete m_dialog;
	m_dialog = new MainDialog(this);
	int option = m_dialog->exec();
	m_dialog->hide();
	int m_dialog_point_index = m_dialog->getPointValue();
	this->setPointValue(m_dialog_point_index);
	army_choice = m_dialog->getArmyChoice();
	delete unit_select;
	unit_select = new QComboBox(main_frame);
	unit_select->addItem("Lords");
	unit_select->addItem("Heros");
	unit_select->addItem("Core");
	unit_select->addItem("Special");
	unit_select->addItem("Rare");
	unit_select->addItem("Special Characters");
	setUnitString(this->unit_select->currentText());
	connect(unit_select, SIGNAL(activated(int)), this, SLOT(selectUnitType()));
	right_inner_layout_top->insertWidget(1, unit_select, 10, Qt::AlignLeft);
	if(option == 1)
	{
		establishArmy();
		this->selectUnitType();
		cout << "The army is now " << army_string->toStdString() << endl;
		setUpEnvironment();
	}
	this->setVisible(true);
}

void MainWindow::saveFile()
{
	QMessageBox::information(this, "Save File", "Do you want to\n save a new File?");
}

void MainWindow::editFile()
{
	QMessageBox::information(this, "Edit File", "Do you want to\n edit a File?");
}

void MainWindow::editUnit()
{
	QMessageBox::information(this, "Edit Unit", "Do you want to\n edit a Unit?");
}

void MainWindow::removeUnit()
{
	QMessageBox::information(this, "Remove Unit", "Do you want to\n remove a Unit?");
}

void MainWindow::selectUnitType()
{
	setUnitString(this->unit_select->currentText());
	delete unit_name_select;
	unit_name_select = new QComboBox(main_frame);
	unit_name_select->setMinimumWidth(200);
	connect(unit_name_select, SIGNAL(activated(int)), this, SLOT(setUpEnvironment()));
	right_inner_layout_top->insertWidget(3, unit_name_select, 100, Qt::AlignLeft);
	QString* file_Name = new QString("ArmiesInfo/");
	file_Name->append(this->army_string);
	file_Name->append("/");
	file_Name->append(this->unit_string);
	file_Name->append(".txt");
	const QString file = *(file_Name);

	QFile f(file);
	f.open(QFile::ReadOnly | QFile::ReadOnly);
	QTextStream ts(&f);
	QString line;
	while(!ts.atEnd())
	{
		line = ts.readLine();
		unit_name_select->addItem(line);
	}
	f.close();
	setUpEnvironment();
}

void MainWindow::setUpEnvironment()
{
	cout << "Going to establish environment " << endl;
	delete _SA;
	unit_string = new QString(unit_name_select->currentText());
	cout << "Finding out what army to build " << endl;
	if(army_string->compare("Beasts of Chaos") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Beasts_of_Chaos_ScrollArea(dock, this->unit_name_select->currentText(), this->unit_select->currentText());
		cout << "Inserting Scroll Area" << endl;
		dock_layout->insertWidget( 1, _SA, 0);
	}
	if(army_string->compare("Bretonnia") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Bretonnia_ScrollArea(this);
	}
	if(army_string->compare("Daemons of Chaos") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Daemons_of_Chaos_ScrollArea(this);
	}
	if(army_string->compare("Dark Elves") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Dark_Elves_ScrollArea(this);
	}
	if(army_string->compare("Dwarfs") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Dwarfs_ScrollArea(this);
	}
	if(army_string->compare("High Elves") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new High_Elves_ScrollArea(this);
	}
	if(army_string->compare("Lizardmen") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Lizardmen_ScrollArea(this);
	}
	if(army_string->compare("Ogre Kingdoms") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Ogre_Kingdoms_ScrollArea(this);
	}
	if(army_string->compare("Orcs & Goblins") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Orcs_n_Goblins_ScrollArea(this);
	}
	if(army_string->compare("Skaven") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Skaven_ScrollArea(this);
	}
	if(army_string->compare("The Empire") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new The_Empire_ScrollArea(this);
	}
	if(army_string->compare("Tomb Kings") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Tomb_Kings_ScrollArea(this);
	}
	if(army_string->compare("Vampire Counts") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Vampire_Counts_ScrollArea(this);
	}
	if(army_string->compare("Warriors of Chaos") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Warriors_of_Chaos_ScrollArea(this);
	}
	if(army_string->compare("Wood Elves") == 0)
	{
		cout << "Setting up environment for " << army_string->toStdString() << endl;
		_SA = new Wood_Elves_ScrollArea(this);
	}
}
