#include "bargraphgl.h"

BarGraphGl::BarGraphGl(
    BarRange_t tmpNumberRange, GLfloat tmpLowerLeftX,
    GLfloat tmpLowerLeftY, GLfloat tmpWidth, GLfloat tmpHeight,
    GLfloat tmpRowHeight, uint32_t tmpRows, QColor tmpBarQColor) :
    mLowerLeftX(tmpLowerLeftX),
    mLowerLeftY(tmpLowerLeftY),
    mWidth(tmpWidth),
    mHeight(tmpHeight),
    mRowHeight(tmpRowHeight),
    mRows(tmpRows),
    mBarQColor(tmpBarQColor),
    mNumberRange(tmpNumberRange),
    mBarValue(mNumberRange.first) {

    mStepValue = (mNumberRange.second - mNumberRange.first)/
        static_cast<GLfloat>(mRows - 1);

    int32_t j = mNumberRange.second;
    for (int32_t i = static_cast<int32_t>(mLowerLeftY) + (mRows * 
        static_cast<int32_t>(mRowHeight)) - 
        static_cast<int32_t>(mRowHeight);
        i >= static_cast<int32_t>(mLowerLeftY); 
        i -= static_cast<int32_t>(mRowHeight)) {

        std::string tmpLabel;
        (i > mLowerLeftY) ?
            tmpLabel = QString::number(j).toStdString():
            tmpLabel = QString::number(0).toStdString();

        Qt::Alignment tmpQtAlignment;
        (i > mLowerLeftY) ?
            tmpQtAlignment = Qt::AlignRight:
            tmpQtAlignment = Qt::AlignCenter;

        BarGraphString tmpBarGraphString(
            tmpLabel,
            mLowerLeftX,
            i,
            mWidth,
            mRowHeight,
            tmpQtAlignment);
         mBarGraphStringVector.push_back(tmpBarGraphString);
         j -= static_cast<int32_t>(mStepValue);
    }    
}

BarGraphGl::BarGraphGl(const BarGraphGl &other) {
    (*this) = other;
}

BarGraphGl &BarGraphGl::operator=(const BarGraphGl &other) {
    mBarGraphStringVector = other.mBarGraphStringVector;
    mLowerLeftX = other.mLowerLeftX;
    mLowerLeftY = other.mLowerLeftY;
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mRowHeight = other.mRowHeight;
    mRows = other.mRows;
    mBarQColor = other.mBarQColor;
    mBarValue = other.mBarValue;
    mNumberRange = other.mNumberRange;
    mStepValue = other.mStepValue;

    return (*this);
}

BarGraphGl::~BarGraphGl() {
    for (std::vector<BarGraphString>::iterator vect_it =
        mBarGraphStringVector.begin();
        vect_it != mBarGraphStringVector.end();
        ++vect_it) {

        vect_it->DeleteGlTexture();
    }
}

void BarGraphGl::UpdateData(GLfloat tmpLowerLeftX, GLfloat tmpLowerLeftY,
        GLfloat tmpWidth, GLfloat tmpHeight, GLfloat tmpRowHeight) {

    mLowerLeftX = tmpLowerLeftX;
    mLowerLeftY = tmpLowerLeftY;
    mWidth = tmpWidth;
    mHeight = tmpHeight;
    mRowHeight = tmpRowHeight;

    uint32_t i = static_cast<uint32_t>(mLowerLeftY)
        + (mRows * static_cast<uint32_t>(mRowHeight)) - 
        static_cast<uint32_t>(mRowHeight);

    for (std::vector<BarGraphString>::iterator vect_it =
        mBarGraphStringVector.begin();
        vect_it != mBarGraphStringVector.end();
        ++vect_it) {

        vect_it->UpdateContentsOnResize(
            mLowerLeftX,
            i,
            mWidth,
            mRowHeight);
        i -= static_cast<uint32_t>(mRowHeight);
    }

    for (std::vector<BarGraphString>::iterator vect_it =
        mBarGraphStringVector.begin();
        vect_it != mBarGraphStringVector.end();
        ++vect_it) {

        vect_it->RegenerateGlTexture();
    }
}

void BarGraphGl::RefreshGLTextures() {
    for (std::vector<BarGraphString>::iterator vect_it =
        mBarGraphStringVector.begin();
        vect_it != mBarGraphStringVector.end();
        ++vect_it) {

        vect_it->RegenerateGlTexture();
    }
}

 void BarGraphGl::setBarValue(const int32_t tmpNewBarValue) {
    mBarValue = tmpNewBarValue;
    mBarGraphStringVector[mBarGraphStringVector.size() - 1].
        setNumberString(QString::number(mBarValue).toStdString());
    for (std::vector<BarGraphString>::iterator vect_it =
        mBarGraphStringVector.begin();
        vect_it != mBarGraphStringVector.end();
        ++vect_it) {

        vect_it->RegenerateGlTexture();
    }
}

void BarGraphGl::RenderContents() {
    for (std::vector<BarGraphString>::iterator vect_it =
        mBarGraphStringVector.begin();
        vect_it != mBarGraphStringVector.end();
        ++vect_it) {

        vect_it->RenderContents();
    }

    assert(mRowHeight > 0 && "Division by zero in bar graph");

    GLfloat tmpBarHeight = 0;
    if (mBarValue > mNumberRange.first) {
        GLfloat tmpLargeRange = (mNumberRange.second - mNumberRange.first);
        GLfloat tmpSmallRange = mBarValue - mNumberRange.first;
        GLfloat tmpRatio = tmpSmallRange/tmpLargeRange;
        tmpBarHeight = tmpRatio * (mHeight - mRowHeight);
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBegin(GL_QUADS);
        glColor4f(mBarQColor.red()/255.0f, mBarQColor.green()/255.0f,
            mBarQColor.blue()/255.0f, 0.50f);

        GLfloat tmpX0 = mLowerLeftX + 1;
        GLfloat tmpY0 = mLowerLeftY + mRowHeight;

        GLfloat tmpX1 = mLowerLeftX + 1;
        GLfloat tmpY1 = mLowerLeftY + tmpBarHeight + mRowHeight;

        GLfloat tmpX2 = mLowerLeftX + mWidth - 1;
        GLfloat tmpY2 = mLowerLeftY + tmpBarHeight + mRowHeight;

        GLfloat tmpX3 = mLowerLeftX + mWidth - 1;
        GLfloat tmpY3 = mLowerLeftY + mRowHeight;


        glVertex2f(tmpX0, tmpY0);
        glVertex2f(tmpX1, tmpY1);
        glVertex2f(tmpX2, tmpY2);
        glVertex2f(tmpX3, tmpY3);

        glColor3f(1.0, 1.0, 1.0);
    glEnd();
    glDisable(GL_BLEND);
}
