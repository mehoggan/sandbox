/*
 * CSVtoDBConverter.h
 *
 *  Created on: Aug 12, 2009
 *      Author: Matthew
 */

#ifndef CSVtoDBConverter_H_
#define CSVtoDBConverter_H_

#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QtAlgorithms>
#include <QVector>
#include <QString>

class CSVtoDBConverter : public QWidget
{
	Q_OBJECT
public:
	CSVtoDBConverter(QString);
	~CSVtoDBConverter();
};

#endif /* CSVtoDBConverter_H_ */
