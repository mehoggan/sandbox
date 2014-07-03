#ifndef TESTER_H
#define TESTER_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtCore/QObject>
#include <QtGui/QApplication>
#include <QtGui/QColor>
#include <vector>
#include <cmath>
#include "bargraphwidget.h"

class Tester : public QObject {
    Q_OBJECT
public:
    BarGraphWidget &mRefBarGraph;
    ColumnDataVector_t &mRefBarGraphData;
    Tester(BarGraphWidget &tmpBarGraph,
        ColumnDataVector_t &tmpBarGraphData) :
        mRefBarGraph(tmpBarGraph),
        mRefBarGraphData(tmpBarGraphData) {

    }

public slots:
    void slotDoTesting() {
        float tmpBar0ValDif =
            mRefBarGraphData[0].second.second -
            mRefBarGraphData[0].second.first;
        float tmpBar1ValDif =
            mRefBarGraphData[1].second.second -
            mRefBarGraphData[1].second.first;
        float tmpBar2ValDif =
            mRefBarGraphData[2].second.second -
            mRefBarGraphData[2].second.first;

        float tmpBar0Val = mRefBarGraphData[0].second.first +
            rand() % static_cast<int>(tmpBar0ValDif);
        float tmpBar1Val = mRefBarGraphData[1].second.first +
            rand() % static_cast<int>(tmpBar1ValDif);
        float tmpBar2Va1 = mRefBarGraphData[2].second.first +
            rand() % static_cast<int>(tmpBar2ValDif);

        mRefBarGraph.setBarValue(0, tmpBar0Val);
        mRefBarGraph.setBarValue(1, tmpBar1Val);
        mRefBarGraph.setBarValue(2, tmpBar2Va1);
    }
};

#endif // TESTER_H
