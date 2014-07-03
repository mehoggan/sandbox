#ifndef BARGRAPHGL_H
#define BARGRAPHGL_H

#include <QtOpenGL/QGLWidget>
#include <vector>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include "../../../include/fpstypedefs.h"
#include "bargraphtypedefs.h"
#include "bargraphstring.h"

class BarGraphGl {
private:
    GLfloat mLowerLeftX;
    GLfloat mLowerLeftY;
    GLfloat mWidth;
    GLfloat mHeight;
    GLfloat mRowHeight;
    uint32_t mRows;
    QColor mBarQColor;
    std::vector<BarGraphString> mBarGraphStringVector;
    BarRange_t mNumberRange;
    int32_t mBarValue;
    GLfloat mStepValue;
   
public:
    BarGraphGl(
        BarRange_t tmpNumberRange = std::make_pair(0, 1),
        GLfloat tmpLowerLeftX = 0, GLfloat tmpLowerLeftY = 0,
        GLfloat tmpWidth = 0, GLfloat tmpHeight = 0,
        GLfloat tmpRowHeight = 0, uint32_t tmpRows = 0,
        QColor tmpBarQColor = QColor(0, 255, 0));
    BarGraphGl(const BarGraphGl &other);
    BarGraphGl &operator=(const BarGraphGl &other);
    ~BarGraphGl();
    void RenderContents();
    void UpdateData(GLfloat tmpLowerLeftX, GLfloat tmpLowerLeftY,
        GLfloat tmpWidth, GLfloat tmpHeight, GLfloat tmpRowHeight);
     void RefreshGLTextures();

    void setBarColor(const QColor &tmpBarQColor) {
        mBarQColor = tmpBarQColor;
    }

    void setBarValue(const int32_t tmpNewBarValue);
};

#endif//BARGRAPHGL_H
