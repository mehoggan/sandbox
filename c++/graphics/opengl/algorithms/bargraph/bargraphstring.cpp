#include "bargraphstring.h"

BarGraphString::BarGraphString(
    std::string tmpNumberString,
    GLfloat tmpLowerLeftXCoord,
    GLfloat tmpLowerLeftYCoord,
    GLfloat tmpWidth,
    GLfloat tmpHeight,
    Qt::Alignment tmpAlignment) :
    mNumberString(tmpNumberString),
    mLowerLeftXCoord(tmpLowerLeftXCoord),
    mLowerLeftYCoord(tmpLowerLeftYCoord),
    mWidth(tmpWidth),
    mHeight(tmpHeight),
    mTextureId(0),
    mFirstInitialRender(true),
    mQtAlignment(tmpAlignment | Qt::AlignVCenter) {

}

BarGraphString::~BarGraphString() {
    if (mTextureId != 0) {
        glDeleteTextures(1, &mTextureId);
    }
}

BarGraphString::BarGraphString(const BarGraphString &other) {
    (*this) = other;
}

BarGraphString &BarGraphString::operator=(const BarGraphString &other) {
    mNumberString = other.mNumberString;
    mLowerLeftXCoord = other.mLowerLeftXCoord;
    mLowerLeftYCoord = other.mLowerLeftYCoord;
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mQtAlignment = other.mQtAlignment;
    mTextureId = 0;
    mFirstInitialRender = true;

    return (*this);
}

void BarGraphString::GenerateGlTexture() {
    const uint32_t tmpFontSize = 6;

    uint32_t tmpWidth = static_cast<uint32_t>(mWidth);
    uint32_t tmpHeight = static_cast<uint32_t>(mHeight);
    QImage tmpQImage(tmpWidth, tmpHeight, QImage::Format_ARGB32);

    QPainter tmpQPainter;
    tmpQPainter.begin(&tmpQImage);
        tmpQPainter.setBackgroundMode(Qt::TransparentMode);
        tmpQPainter.setRenderHint(QPainter::Antialiasing, true);
        tmpQPainter.setBrush(QBrush(QColor(234, 234, 234),
            Qt::SolidPattern));
        tmpQPainter.drawRect(0, 0, static_cast<int>(mWidth), 
            static_cast<int>(mHeight));
        tmpQPainter.setPen(QPen(Qt::black, 1));
        tmpQPainter.setFont(QFont("Arial", tmpFontSize));
        tmpQPainter.drawText(
            QRectF(QPointF(0, 0), QSizeF(mWidth - 2.0, mHeight - 2.0)),
            mQtAlignment,
            QString(mNumberString.c_str()));
    tmpQPainter.end();
    tmpQImage = QImage(QGLWidget::convertToGLFormat(tmpQImage));

    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tmpQImage.width(),
        tmpQImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
        tmpQImage.bits());
    GLuint tmpGLError = glGetError();
    if (tmpGLError != GL_NO_ERROR) {
       qDebug() << tmpGLError;
    }
}

void BarGraphString::DeleteGlTexture() {
    //if (mTextureId != 0) {
        glDeleteTextures(1, &mTextureId);
    //} else {
    //    QApplication::exit(1);
    //}
}

void BarGraphString::RegenerateGlTexture() {
    DeleteGlTexture();
    mFirstInitialRender = true;
}

void BarGraphString::UpdateContentsOnResize(GLfloat tmpLowerLeftXCoord,
    GLfloat tmpLowerLeftYCoord, GLfloat tmpWidth,
    GLfloat tmpHeight) {

    mLowerLeftXCoord = tmpLowerLeftXCoord;
    mLowerLeftYCoord = tmpLowerLeftYCoord;
    mWidth = tmpWidth;
    mHeight = tmpHeight;
}

void BarGraphString::RenderContents() {
    if (mFirstInitialRender) {
        GenerateGlTexture();
        mFirstInitialRender = false;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glBegin(GL_QUADS);
         glColor3f(0.98f, 0.98f, 0.98f);
         glTexCoord2f(0.0, 0.0);
         glVertex2f(mLowerLeftXCoord, mLowerLeftYCoord);
         glTexCoord2f(0.0, 1.0);
         glVertex2f(mLowerLeftXCoord, mLowerLeftYCoord + mHeight);
         glTexCoord2f(1.0, 1.0);
         glVertex2f(mLowerLeftXCoord + mWidth, mLowerLeftYCoord + mHeight);
         glTexCoord2f(1.0, 0.0);
         glVertex2f(mLowerLeftXCoord + mWidth, mLowerLeftYCoord);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
