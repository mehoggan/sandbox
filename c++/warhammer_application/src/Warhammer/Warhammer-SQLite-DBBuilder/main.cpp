/*
 * main.cpp
 *
 *  Created on: Aug 12, 2009
 *      Author: Matthew
 */

#include <QApplication>
#include "DBBuilder.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	DBBuilder* dbbuild = new DBBuilder();
	delete dbbuild;
	dbbuild = NULL;
	return a.exec();
}
