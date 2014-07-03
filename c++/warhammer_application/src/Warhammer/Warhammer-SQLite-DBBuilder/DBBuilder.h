/*
 * DBBuilder.h
 *
 *  Created on: Aug 12, 2009
 *      Author: Matthew
 */

#ifndef DBBUILDER_H_
#define DBBUILDER_H_

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

class DBBuilder : public QWidget
{
	Q_OBJECT
public:
	DBBuilder();
	~DBBuilder();
	QString processQuery(QString);
	QString processPath(QString);
	QSqlDatabase db;
};

#endif /* DBBUILDER_H_ */
