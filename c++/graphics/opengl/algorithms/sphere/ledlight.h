#ifndef LEDLIGHT_H
#define LEDLIGHT_H

#include <QtOpenGL/QGLWidget>
#include <QtGui/QApplication>
#include <QtGui/QColor>

#include <cmath>

#include "../../../include/fpstypedefs.h"

class LedLight {
private:
    QColor mCurrentColor;
    GLfloat mCenterXCoord;
    GLfloat mCenterYCoord;
    GLfloat mDiameter;
    GLfloat mPi;
    GLuint mBulbNumber;
    bool mFirstInitialRender;

public:
    LedLight(QColor tmpCurrentColor = QColor(155, 155, 155),
        GLfloat tmpCenterXCoord = 0.00f, GLfloat tmpCenterYCoord = 0.00f,
        GLfloat tmpDiameter = 0.00f);
    LedLight(const LedLight &other);
    LedLight &operator=(const LedLight &other);
    ~LedLight();
    void RenderContents();
    void GenerateBulbs();

    void setCurrentColor(const QColor &tmpNewColor) {
        mCurrentColor = tmpNewColor;
    }
};

#endif//LEDLIGHT_H
