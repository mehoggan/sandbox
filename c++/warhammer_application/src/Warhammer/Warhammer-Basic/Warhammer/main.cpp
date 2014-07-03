/*
 * main.cpp
 *
 *  Created on: Jul 26, 2009
 *      Author: Matthew
 */

#include <iostream>
#include <QtGui>
#include <qapplication.h>
#include <QSqlDatabase>
#include <stdlib.h>
#include "mainwindow.h"

using namespace std;

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow* mainwindow = new MainWindow();
	a.exec();
	delete mainwindow;
	return 0;
}
