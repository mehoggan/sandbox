/*
 * Beasts_of_Chaos_ScrollArea.h
 *
 *  Created on: Aug 13, 2009
 *      Author: Matthew
 */

#ifndef BEASTS_OF_CHAOS_SCROLLAREA_H_
#define BEASTS_OF_CHAOS_SCROLLAREA_H_

#include <QScrollArea>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QPixmap>
#include <QFrame>

class Beasts_of_Chaos_ScrollArea : public QScrollArea
{
	Q_OBJECT
public:
	Beasts_of_Chaos_ScrollArea(QWidget *parent, const QString, const QString);
	~Beasts_of_Chaos_ScrollArea();

	QSqlDatabase db;
	bool ok;

	QVBoxLayout* character_sheet;
	QGridLayout* model_stats;
private:
        QWidget *parent;
	QFrame* central_frame;
	QString unit_type;
	QString unit_name;
	QString pictureDir();
	void statsLayout(QString[]);
	void stats_with_Mount_Layout(QString[], QString[]);
	void stats_with_Chariot_Layout(QString[], QString[], QString[], QString[]);
};

#endif /* BEASTS_OF_CHAOS_SCROLLAREA_H_ */
