/*
 * Beasts_of_Chaos_ScrollArea.cpp
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#include <iostream>
#include "Beasts_of_Chaos_ScrollArea.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QPixmap>
#include <QMessageBox>
#include <QFrame>

using namespace std;

Beasts_of_Chaos_ScrollArea::Beasts_of_Chaos_ScrollArea(QWidget *parent, const QString unit_name, const QString unit_type) : parent(parent)
{
	this->unit_name = unit_name;
	this->unit_type = unit_type;

	setWidgetResizable(true);
	central_frame = new QFrame();

	QSqlDatabase::removeDatabase("QSQLITE");
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setHostName("Matthew");
	db.setDatabaseName("Warhammer-Basic.db");
	db.setUserName("Matthew");
	db.setPassword("heed666~");
	db.database("Warhammer-Basic.db", true);
	ok = db.open();

	if(unit_name.compare("Beastlord") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Doombull") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Great Bray-Shaman") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Wargor") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Bray_Shaman") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Beast Herd") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Bestigor Herd") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Tuskgor Chariot") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Warhounds of Chaos") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Chaos Trolls") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Chaos Ogres") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Centigor") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Minotaurs") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Dragon Ogres") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Dragon Ogre Shaggoth") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Chaos Giant") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Spawn of Chaos") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Khazrak the One-Eye") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
	if(unit_name.compare("Gorthor the Beastlord") == 0)
	{
		cout << "Building Scroll Area for " << unit_name.toStdString() << endl;
		QString stats_array[10] = {unit_name, "5", "7", "3", "5", "4", "3", "6", "4", "9"};
		QString assistant[10] = {"Bagrar", "-", "4", "3", "4", "-", "-", "4", "2", "7"};
		QString tuskgor[10] = {"Tuskgor", "-", "-", "-", "5", "5", "4", "-", "-", "-"};
		QString chariot[10] = {"Chariot", "7", "3", "-", "4", "-", "-", "2", "1", "-"};
		character_sheet = new QVBoxLayout();
		/*
		 * Top Part of Character_Sheet Layout
		 */
		QHBoxLayout* top = new QHBoxLayout();
		QLabel* model_name = new QLabel(unit_name);
		model_name->setFrameStyle(3);
		model_name->setAlignment(Qt::AlignCenter);
		top->insertWidget(0, model_name, 0);
		QLabel* model_points = new QLabel("292");
		model_points->setFrameStyle(3);
		model_points->setAlignment(Qt::AlignCenter);
		top->insertWidget(1, model_points, 0);
		QLabel* model_picture = new QLabel();
		QPixmap* image = new QPixmap(pictureDir());
		model_picture->setPixmap(*(image));
		model_picture->setFrameStyle(3);
		top->insertWidget(2, model_picture, 0);
		stats_with_Chariot_Layout(stats_array, assistant, tuskgor, chariot);
		top->insertLayout(3, model_stats, 0);
		character_sheet->insertLayout(0, top, 0);
		top->addStretch();
		/*
		 * Main Part of Character_Sheet Layout
		 */

		central_frame->setLayout(character_sheet);
		this->setWidget(central_frame);
		character_sheet->addStretch();
	}
	if(unit_name.compare("Morghur, Master of Skulls") == 0)
	{
		cout << unit_name.toStdString() << endl;
	}
}

Beasts_of_Chaos_ScrollArea::~Beasts_of_Chaos_ScrollArea()
{
	cout << "Closing Database" << endl;
	db.close();
	QSqlDatabase::removeDatabase("QSQLITE");
}

QString Beasts_of_Chaos_ScrollArea::pictureDir()
{
	QString dir("ArmiesInfo");
	dir.append("/");
	dir.append("Beasts of Chaos");
	dir.append("/");
	dir.append(unit_type);
	dir.append("/");
	dir.append(unit_name);
	dir.append(".jpg");
	return dir;
}

void Beasts_of_Chaos_ScrollArea::statsLayout(QString stats[10])
{
	QString header[10] = {"", "M", "WS", "BS", "S", "T", "W", "I", "A", "Ld"};
	model_stats = new QGridLayout();
	for(int x = 0; x < 9; x++)
	{
		QLabel* top_stat = new QLabel(header[x]);
		top_stat->setFrameStyle(3);
		QLabel* bottom_stat = new QLabel(stats[x]);
		bottom_stat->setFrameStyle(3);
		model_stats->addWidget(top_stat, 0, x, 0);
		model_stats->addWidget(bottom_stat, 1, x, 0);
	}
}

void Beasts_of_Chaos_ScrollArea::stats_with_Mount_Layout(QString stats[10], QString stats_mount[10])
{
	QString header[10] = {"", "M", "WS", "BS", "S", "T", "W", "I", "A", "Ld"};
	model_stats = new QGridLayout();
	for(int x = 0; x < 9; x++)
	{
		QLabel* top_stat = new QLabel(header[x]);
		top_stat->setFrameStyle(3);
		QLabel* bottom_stat = new QLabel(stats[x]);
		bottom_stat->setFrameStyle(3);
		QLabel* pet_stat = new QLabel(stats_mount[x]);
		pet_stat->setFrameStyle(3);
		model_stats->addWidget(top_stat, 0, x, 0);
		model_stats->addWidget(bottom_stat, 1, x, 0);
		model_stats->addWidget(pet_stat, 2, x, 0);
	}
}

void Beasts_of_Chaos_ScrollArea::stats_with_Chariot_Layout(QString stats[10], QString stats_assistant[10], QString tuskgor_stats[10], QString chariot_stats[10])
{
	QString header[10] = {"", "M", "WS", "BS", "S", "T", "W", "I", "A", "Ld"};
	model_stats = new QGridLayout();
	for(int x = 0; x < 10; x++)
	{
		QLabel* top = new QLabel(header[x]);
		top->setFrameStyle(3);
		top->setAlignment(Qt::AlignRight);
		QLabel* character = new QLabel(stats[x]);
		character->setFrameStyle(3);
		character->setAlignment(Qt::AlignCenter);
		QLabel* assistant = new QLabel(stats_assistant[x]);
		assistant->setFrameStyle(3);
		assistant->setAlignment(Qt::AlignCenter);
		QLabel* tuskgor = new QLabel(tuskgor_stats[x]);
		tuskgor->setFrameStyle(3);
		tuskgor->setAlignment(Qt::AlignCenter);
		QLabel* chariot = new QLabel(chariot_stats[x]);
		chariot->setFrameStyle(3);
		chariot->setAlignment(Qt::AlignCenter);
		model_stats->addWidget(top, 0, x, 0);
		model_stats->addWidget(character, 1, x, 0);
		model_stats->addWidget(assistant, 2, x, 0);
		model_stats->addWidget(tuskgor, 3, x, 0);
		model_stats->addWidget(chariot, 4, x, 0);
	}
}
