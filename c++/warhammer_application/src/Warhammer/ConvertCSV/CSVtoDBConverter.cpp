/*
 * CSVtoDBConverter.cpp
 *
 *  Created on: Aug 12, 2009
 *      Author: Matthew
 */

#include "CSVtoDBConverter.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#include <QtAlgorithms>
#include <QVector>
#include <QString>
#include <iostream>

using namespace std;
CSVtoDBConverter::CSVtoDBConverter(QString army_Spreadsheet)
{
	const QString read("Reading From");
	const QString write("Write To");
	cout << "Inside constructor" << endl;
	int line_count = 0;

	QString* file_Name1 = new QString(army_Spreadsheet);
	file_Name1->append("_Spreadsheet.csv");
	const QString file_Name1_Const(*(file_Name1));
	QFile f1(file_Name1_Const);
	if(!f1.open(QFile::ReadOnly | QFile::ReadOnly))
	{
		//QMessageBox::warning(0, "Error Opening File", file_Name1_Const, 0, 0);
		exit(0);
	}
	else
	{
		//QMessageBox::information(0, read, file_Name1_Const, 0, 0);
	}

	QString* file_Name2 = new QString("/home/Matthew/workspace/Warhammer-SQLite-DBBuilder/ArmiesInfo/");
	file_Name2->append(army_Spreadsheet);
	file_Name2->append("_Spreadsheet.txt");
	const QString file_Name2_Const(*(file_Name2));
	QFile f2(file_Name2_Const);
	if(!f2.open(QFile::WriteOnly | QFile::WriteOnly))
	{
		//QMessageBox::warning(0, "Error Writing File", file_Name2_Const, 0, 0);
		exit(0);
	}
	else
	{
		//QMessageBox::information(0, write, file_Name2_Const, 0, 0);
	}
	QTextStream ts1(&f1);
	QTextStream ts2(&f2);
	QString line;
	while(!ts1.atEnd())
	{
		line = ts1.readLine();
		if(line_count == 0)
		{
			line.replace("\"", "");
			line.replace("\t", ", ");
			line.replace("  ", " ");
			line.append("\n");
			//QMessageBox::information(this, "Modifying String To (1):", line, 0, 0);
			ts2 << line;
		}
		else if(line_count == 1)
		{
			line.replace("\"", "");
			line.replace("\t", ", ");
			line.replace("  ", " ");
			line.remove(line.length() - 2, line.length() - 1);
			line.append("\n");
			//QMessageBox::information(this, "Modifying String To (2):", line, 0, 0);
			ts2 << line;
		}
		else
		{
			line.replace("\'", "\'");
			line.replace("'\"", "'");
			line.replace("\" '", "'");
			line.replace("\"", "'");
			line.replace("\t", ", ");
			line.replace("  ", " ");
			line.remove(line.length() - 2, line.length() - 1);
			line.append("\n");
			//QMessageBox::information(this, "Modifying String To (3):", line, 0, 0);
			ts2 << line;
		}
		line_count++;
	}
	f1.close();
	f2.close();
	cout << "DONE!!!\n" << endl;
}
CSVtoDBConverter::~CSVtoDBConverter()
{
}
