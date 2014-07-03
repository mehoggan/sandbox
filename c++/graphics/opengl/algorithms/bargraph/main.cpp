#include "tester.h"

int main(int argc, char *argv[]) {
    QApplication tmpQApp(argc, argv);
    BarLabelAndColor_t
        tmpBarLabelAndColor0(QString("FWD(W)"), QColor(0, 255, 0));
    BarRange_t tmpBarRange0(200, 2000);
    ColumnData_t tmpColumn0(tmpBarLabelAndColor0, tmpBarRange0);

    BarLabelAndColor_t 
        tmpBarLabelAndColor1(QString("REV(W)"), QColor(0, 0, 255));
    BarRange_t tmpBarRange1(8, 80);
    ColumnData_t tmpColumn1(tmpBarLabelAndColor1, tmpBarRange1);

    BarLabelAndColor_t
        tmpBarLabelAndColor2(QString("REV(W)"), QColor(255, 0, 0));
    BarRange_t tmpBarRange2(0, 10000);
    ColumnData_t tmpColumn2(tmpBarLabelAndColor2, tmpBarRange2);

    ColumnDataVector_t tmpBarGraphColumnData;
    tmpBarGraphColumnData.push_back(tmpColumn0);
    tmpBarGraphColumnData.push_back(tmpColumn1);
    tmpBarGraphColumnData.push_back(tmpColumn2);

    BarGraphWidget tmpBarGraphWidget(10, tmpBarGraphColumnData);
    tmpBarGraphWidget.resize(300, 400);
    tmpBarGraphWidget.show();
    QTimer mTimer;
    Tester mTester(tmpBarGraphWidget, tmpBarGraphColumnData);
    QObject::connect(&mTimer, SIGNAL(timeout()), &mTester,
        SLOT(slotDoTesting()));
     mTimer.start(1000);

    tmpQApp.exec();
}
