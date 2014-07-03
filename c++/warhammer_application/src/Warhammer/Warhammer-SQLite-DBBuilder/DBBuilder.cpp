/*
 * DBBuilder.cpp
 *
 *  Created on: Aug 12, 2009
 *      Author: Matthew
 */

#include "DBBuilder.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QtAlgorithms>
#include <QVector>
#include <QString>

DBBuilder::DBBuilder()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setHostName("Matthew");
	db.setDatabaseName("Warhammer-Basic.db");
	//db.setUserName("Mattew");
	//db.setPassword("heed666~1");
	db.database("Warhammer-Basic.db", true);
	bool ok = db.open();

	QVector<QString>* vector0 = new QVector<QString>();
	QString armies_Array[15] =
	{
				"Dwarfs", "Orcs & Goblins", "The Empire", "High Elves",
				"Dark Elves", "Wood Elves", "Skaven", "Beasts of Chaos",
				"Lizardmen", "Vampire Counts", "Tomb Kings", "Bretonnia", "Ogre Kingdoms",
				"Warriors of Chaos", "Daemons of Chaos"
	};

	for(int x = 0; x < 15; x++)
	{
		vector0->insert(x, armies_Array[x]);
	}

	qSort(vector0->begin(), vector0->end());

	for(int x = 0; x < 15; x++)
	{
		QString* file_Name = new QString("ArmiesInfo/");
		file_Name->append(vector0->at(x));
		file_Name->append("_Spreadsheet.txt");
		QString file_Name_Processed = processPath(*(file_Name));
		const QString file1 = (file_Name_Processed);

		QFile f(file1);
		if(!f.open(QFile::ReadOnly | QFile::ReadOnly))
		{
			QMessageBox::warning(0, "Error Opening File", file1, 0, 0);
			exit(0);
		}
		else
		{
			QMessageBox::information(0, "Will Open File", file1);
		}

		QTextStream ts(&f);
		QString line;
		QString table_build = ts.readLine();
		QString columns = ts.readLine();
		QString table = processQuery(*(file_Name));
		this->processQuery(table);
		int command = 0;
		QSqlQuery exec_query;
		while(!ts.atEnd())
		{
			if(command == 0)
			{
				QString query = ("DROP TABLE ");
				query.append(table);
				query.append(";");
				if(exec_query.exec(query))
				{
					QMessageBox::information(this, "Drop Table", query);
				}
				else
				{
					QString could_not = "Could not execute ";
					could_not.append(query);
					QMessageBox::warning(0, "ERROR", could_not, "Exit");
				}
				query = "CREATE TABLE ";
				query.append(table);
				query.append(" (");
				query.append(table_build);
				query.append(");");
				if(exec_query.exec(query))
				{
					QMessageBox::information(this, "Create Table", query);
				}
				else
				{
					QString could_not = "Could not execute ";
					could_not.append(query);
					QMessageBox::warning(0, "ERROR", could_not, "Exit");
					//exit(0);
				}
			}
			else
			{
				line = ts.readLine();
				QString query = ("INSERT INTO ");
				query.append(table);
				query.append(" (");
				query.append(columns);
				query.append(") VALUES (");
				query.append(line);
				query.append(");");
				if(exec_query.exec(query))
				{
					QMessageBox::information(this, "Insert Into Table", query);
				}
				else
				{
					QString could_not = "Could not execute ";
					could_not.append(query);
					QMessageBox::warning(0, "ERROR", could_not, "Exit");
					exit(0);
				}
			}
			command++;
		}
	}
}

DBBuilder::~DBBuilder()
{
	db.close();
	QMessageBox::information(this, "Closing Connection", "Database Closed");
}

QString DBBuilder::processPath(QString process_string)
{
	QString return_string(process_string);
	return_string.replace(" ", "_");
	return return_string;
}

QString DBBuilder::processQuery(QString process_string)
{
	QString return_string(process_string);
	return_string.replace("-", "_");
	return_string.replace(":", "");
	return_string.replace(" ", "_");
	return_string.replace('/', '_');
	return_string.remove(".txt", Qt::CaseSensitive);
	return_string.remove("ArmiesInfo", Qt::CaseSensitive);
	return_string.replace(0, 1, "");
	return_string.replace(",", "");
	return return_string;
}
