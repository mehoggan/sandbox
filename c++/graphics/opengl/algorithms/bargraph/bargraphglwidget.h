#ifndef BARGRAPHGLWIDGET_H
#define BARGRAPHGLWIDGET_H

class BarGraphWidget;

#include <QtOpenGL/QGLWidget>
#include <QtGui/QColor>
#include <QtGui/QResizeEvent>
#include <QtCore/QSize>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include "../../../include/fpstypedefs.h"
#include "bargraphtypedefs.h"
#include "bargraphgl.h"

class BarGraphGlWidget : public QGLWidget { 
    Q_OBJECT
private:
    BarGraphWidget *mPtrParent;
    uint32_t mRows;
    uint32_t mCols;
    uint32_t mColumnWidth;
    uint32_t mRowHeight;
    uint32_t mWidth;
    uint32_t mHeight;
    ColumnDataVector_t mColumnDataVector;
    std::vector<BarGraphGl> mBarGraphVector;

protected:
    virtual void resizeGL(int width, int height);
    virtual void resizeEvent(QResizeEvent *event);

public:
    BarGraphGlWidget(BarGraphWidget *tmpPtrParent,
        uint32_t tmpRows, ColumnDataVector_t &tmpColumnDataVector);
    void UpdateOnParentResize(uint32_t tmpColumnWidth, uint32_t tmpRowHeight);
    void RefreshGLTextures();
    void setBarColor(const uint32_t tmpCol, const QColor &tmpNewColor);
    void setBarValue(const uint32_t tmpCol, const int32_t tmpNewBarValue);

public slots:
    virtual void updateGL();
};

#endif//BARGRAPHGLWIDGET_H
