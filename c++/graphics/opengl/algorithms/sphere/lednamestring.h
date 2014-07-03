#ifndef LEDNAMESTRING_H
#define LEDNAMESTRING_H

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

#include "../../../include/fpstypedefs.h"

class LedNameString {
private:
    std::string mNameString;
    GLfloat mLowerLeftXCoord;
    GLfloat mLowerLeftYCoord;
    GLfloat mWidth;
    GLfloat mHeight;
    uint32_t mFontSize;
    GLuint mTextureId;
    bool mFirstInitialRender;

    void GenerateGlTexture();
public:
    LedNameString(
        uint32_t tmpFontSize = 8,
        std::string tmpNameString = std::string(""),
        GLfloat tmpLowerLeftXCoord = 0.00f,
        GLfloat tmpLowerLeftYCoord = 0.00f,
        GLfloat tmpWidth = 0.00f,
        GLfloat tmpHeight = 0.00f);
    ~LedNameString();
    LedNameString(const LedNameString &other);
    LedNameString &operator=(const LedNameString &other);
    void RenderContents();

    void DeleteGlTexture();
    void RegenerateGlTexture(uint32_t tmpWidth, uint32_t tmpHeight);
    void RegenerateGlTexture();
};

#endif//LEDNAMESTRING_H
