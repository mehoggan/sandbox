/*
 * main.cpp
 *
 *  Created on: Aug 12, 2009
 *      Author: Matthew
 */

#include <QApplication>
#include "CSVtoDBConverter.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	CSVtoDBConverter* CsvConverter = new CSVtoDBConverter("Beasts_of_Chaos");
	delete CsvConverter;
	CsvConverter = NULL;
	return a.exec();
}
