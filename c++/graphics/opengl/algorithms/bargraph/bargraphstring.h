#ifndef BARGRAPHSTRING_H
#define BARGRAPHSTRING_H

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtOpenGL/QGLWidget>
#include <QtGui/QApplication>
#include <QtGui/QImage>
#include <QtGui/QMessageBox>
#include <QtGui/QPainter>

#include <iostream>
#include <string>
#include <stdint.h>
#include "bargraphtypedefs.h"
#include "../../../include/fpstypedefs.h"

class BarGraphString {
private:
    std::string mNumberString;
    GLfloat mLowerLeftXCoord;
    GLfloat mLowerLeftYCoord;
    GLfloat mWidth;
    GLfloat mHeight;
    GLuint mTextureId;
    bool mFirstInitialRender;
    Qt::Alignment mQtAlignment;

    void GenerateGlTexture();
public:
    BarGraphString(std::string tmpNumberString,
        GLfloat tmpLowerLeftXCoord = 0.00f, 
        GLfloat tmpLowerLeftYCoord = 0.00f,
        GLfloat tmpWidth = 0.00f,
        GLfloat tmpHeight = 0.00f,
        Qt::Alignment tmpAlignment = Qt::AlignRight);
    ~BarGraphString();
    BarGraphString(const BarGraphString &other);
    BarGraphString &operator=(const BarGraphString &other);
    void RenderContents();

    void DeleteGlTexture();
    void RegenerateGlTexture();
    void UpdateContentsOnResize(GLfloat tmpLowerLeftXCoord,
        GLfloat tmpLowerLeftYCoord, GLfloat tmpWidth,
        GLfloat tmpHeight);

    void setNumberString(const std::string &tmpNumberString) {
        mNumberString = tmpNumberString;
    }
};

#endif//BARGRAPHSTRING_H
