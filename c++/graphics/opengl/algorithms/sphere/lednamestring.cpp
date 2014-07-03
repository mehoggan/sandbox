#include "lednamestring.h"

LedNameString::LedNameString(
    uint32_t tmpFontSize,
    std::string tmpNameString,
    GLfloat tmpLowerLeftXCoord,
    GLfloat tmpLowerLeftYCoord,
    GLfloat tmpWidth,
    GLfloat tmpHeight) :
    mNameString(tmpNameString),
    mLowerLeftXCoord(tmpLowerLeftXCoord),
    mLowerLeftYCoord(tmpLowerLeftYCoord),
    mWidth(tmpWidth),
    mHeight(tmpHeight),
    mFontSize(tmpFontSize),
    mTextureId(0),
    mFirstInitialRender(true) {

}

LedNameString::~LedNameString() {
    if (mTextureId != 0) {
        glDeleteTextures(1, &mTextureId);
    }
}

LedNameString::LedNameString(const LedNameString &other) {
    (*this) = other;
}

LedNameString &LedNameString::operator=(const LedNameString &other) {
    mNameString = other.mNameString;
    mLowerLeftXCoord = other.mLowerLeftXCoord;
    mLowerLeftYCoord = other.mLowerLeftYCoord;
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mFontSize = other.mFontSize;
    mTextureId = 0;
    mFirstInitialRender = true;

    return (*this);
}

void LedNameString::GenerateGlTexture() {
    QFont tmpQFont("Arial", mFontSize);

    QImage tmpQImage(static_cast<int>(mWidth),
        static_cast<int>(mHeight), QImage::Format_ARGB32);

    QPainter tmpQPainter;
    tmpQPainter.begin(&tmpQImage);
        tmpQPainter.setRenderHint(QPainter::Antialiasing, true);
        tmpQPainter.setPen(QPen(QColor(235, 235, 235)));
        tmpQPainter.setBrush(QBrush(QColor(235, 235, 235), Qt::SolidPattern));
        tmpQPainter.drawRect(0, 0, static_cast<int32_t>(mWidth), 
            static_cast<int32_t>(mHeight));
        tmpQPainter.setPen(QPen(Qt::black, 1));
        tmpQPainter.setFont(tmpQFont);
        tmpQPainter.drawText(
            QRectF(QPointF(0.0, 0.0), QSizeF(mWidth, mHeight)),
            QString(mNameString.c_str()));
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
    }
}

void LedNameString::DeleteGlTexture() {
    if (mTextureId) {
        glDeleteTextures(1, &mTextureId);
    }
}

void LedNameString::RegenerateGlTexture() {
    DeleteGlTexture();
    mFirstInitialRender = true;
}

void LedNameString::RegenerateGlTexture(uint32_t tmpWidth,
    uint32_t tmpHeight) {

    DeleteGlTexture();
    mWidth = tmpWidth;
    mHeight = tmpHeight;
    mFirstInitialRender = true;
}

void LedNameString::RenderContents() {
    if (mFirstInitialRender) {
        GenerateGlTexture();
        mFirstInitialRender = false;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
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
    glDisable(GL_BLEND);
}
