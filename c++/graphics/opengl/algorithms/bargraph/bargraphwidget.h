#ifndef BARGRAPHWIDGET_H
#define BARGRAPHWIDGET_H

#include <QtCore/QSize>
#include <QtGui/QWidget>
#include <QtGui/QColor>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QResizeEvent>
#include <QtGui/QVBoxLayout>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdint.h>
#include <assert.h>
#include <stdexcept>
#include <math.h>
#include "../../../include/fpstypedefs.h"
#include "bargraphtypedefs.h"
#include "bargraphglwidget.h"

class BarGraphWidget : public QWidget {
    Q_OBJECT
private:
    uint32_t mWidth;
    uint32_t mHeight;
    ColumnDataVector_t mColumnDataVector;
    uint32_t mCols;
    uint32_t mRows;
    std::vector<QLabel *> mColumnQLabelVector;
    QHBoxLayout *mPtrQLabelHBoxLayout;
    QVBoxLayout *mPtrMainVBoxLayout;
    BarGraphGlWidget *mPtrBarGraphGlWidget;
    uint32_t mColumnWidth;
    uint32_t mRowHeight;

    void ResizeCalculations();
    void SetupLayouts();
    BarGraphWidget(const BarGraphWidget &other);   
    BarGraphWidget &operator=(const BarGraphWidget &other);

protected:
    virtual void resizeEvent(QResizeEvent *event);

public:
    BarGraphWidget(uint32_t tmpRows, ColumnDataVector_t tmpColumnDataVector);
    ~BarGraphWidget();
    void RefreshGLTextures();
    void setBarColor(const uint32_t tmpCol, const QColor &tmpNewColor);
    void setBarValue(const uint32_t tmpCol, const int32_t tmpNewBarValue);

    uint32_t ColumnWidth() {
        return mColumnWidth;
    }

    uint32_t RowHeight() {
        return mRowHeight;
    }
public slots:
    void slotTimerUpdateRequest();
};

#endif //BARGRAPHWIDGET_H
