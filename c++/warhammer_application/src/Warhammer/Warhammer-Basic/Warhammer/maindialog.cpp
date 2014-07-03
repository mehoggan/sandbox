/*
 * maindialog.cpp
 *
 *  Created on: Jul 27, 2009
 *      Author: Matthew
 */

#include <QApplication>
#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QDesktopWidget>
#include <QDialog>
#include <QMessageBox>
#include "maindialog.h"
#include "armylistcontainer.h"

MainDialog::MainDialog(QWidget* parent) : QDialog(parent)
{
	p_parent = parent;
	army_choice = -1;

	QGridLayout* g_layout = new QGridLayout();
	QHBoxLayout* h_layout1 = new QHBoxLayout();
	QHBoxLayout* h_layout2 = new QHBoxLayout();
	QHBoxLayout* h_layout3 = new QHBoxLayout();

	QLabel* label_image = new QLabel();
	QPixmap main_image("WarHammer.jpg");
	label_image->setPixmap(main_image);
	g_layout->addWidget(label_image, 0, 0, Qt::AlignTop);

	comboBox = new QComboBox();
	vector_list = new ArmyListContainer();
	for(int x = -1; x < 15; x++)
	{
		if(x == -1)
		{
			comboBox->addItem("(None)");
		}
		else
		{
			comboBox->addItem(vector_list->vector->at(x));
		}
	}
	delete vector_list;
	QLabel* army_choice = new QLabel("Select Your Army: ");
	army_choice->setMinimumWidth(100);
	comboBox->setMinimumWidth(220);
	h_layout1->addWidget(army_choice, 0, Qt::AlignRight);
	h_layout1->addWidget(comboBox, 100, Qt::AlignLeft);

	pointBox = new QComboBox(this);
	pointBox->addItem("0");
	pointBox->addItem("500");
	pointBox->addItem("750");
	pointBox->addItem("1000");
	pointBox->addItem("1250");
	pointBox->addItem("1500");
	pointBox->addItem("1750");
	pointBox->addItem("2000");
	pointBox->addItem("2250");
	pointBox->addItem("2500");
	pointBox->addItem("2750");
	pointBox->addItem("3000");
	pointBox->addItem("3250");
	pointBox->addItem("3500");
	pointBox->addItem("3750");
	pointBox->addItem("4000");
	pointBox->setMinimumWidth(220);
	QLabel* point_choice = new QLabel("Total Points: ");
	point_choice->setMinimumWidth(119);
	h_layout2->addWidget(point_choice, 0, Qt::AlignRight);
	h_layout2->addWidget(pointBox, 1, Qt::AlignLeft);

	ok = new QPushButton(tr("Ok"));
	cancel = new QPushButton(tr("Cancel"));
	h_layout3->addWidget(ok);
	h_layout3->addWidget(cancel);

	g_layout->addLayout(h_layout1, 1, 0, 0);
	g_layout->addLayout(h_layout2, 2, 0, 0);
	g_layout->addLayout(h_layout3, 3, 0, 0);

	QDesktopWidget* desktop = new QDesktopWidget();
	int top = desktop->height()/4;
	int left = desktop->width()/3;
	this->setLayout(g_layout);
	this->setMaximumSize(200, 300);
	this->setGeometry(left, top, this->maximumHeight(), this->maximumWidth());

	this->connect(ok, SIGNAL(clicked()), this, SLOT(YesArmyChoice()));
	this->connect(cancel, SIGNAL(clicked()), this, SLOT(NoArmyChoice()));

	this->show();
}

MainDialog::~MainDialog()
{

}

void MainDialog::setArmyChoice(int army_option)
{
	this->army_choice = army_option;
}

int MainDialog::getArmyChoice()
{
	return this->army_choice;
}

void MainDialog::setPointValue(int point_option)
{
	this->point_value = point_option;
}

int MainDialog::getPointValue()
{
	return this->point_value;
}

void MainDialog::YesArmyChoice()
{
	int choice = comboBox->currentIndex();
	setArmyChoice(choice);
	int choice2 = pointBox->currentIndex();
	setPointValue(choice2);
	this->done(1);
}

void MainDialog::NoArmyChoice()
{
	int choice = -1;
	setArmyChoice(choice);
	int choice2 = -1;
	setPointValue(choice2);
	this->done(0);
}
