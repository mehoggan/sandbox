#include "ledpannelglwidget.h"

LedPannelGlWidget::LedPannelGlWidget(
    uint32_t tmpFontSize,
    std::vector<std::vector<std::string> > &tmpLabelVector,
    std::vector<std::vector<QColor> > &tmpInitialColorVector) :
    mLabelVector(tmpLabelVector),
    mInitialColorVector(tmpInitialColorVector),
    mWidth(width()),
    mHeight(height()),
    mFontSize(tmpFontSize) {
    
    /*
     * Perge the data
     */ 
    assert((mLabelVector.size() == mInitialColorVector.size()) && 
        "Number of labels does not match number of initial colors in"
        "construction of LedPannel");
    for (size_t i = 0; i < tmpLabelVector.size(); ++i) {
        assert((mLabelVector[i].size() == mInitialColorVector[i].size()) &&
            "The dimensions of labels and initial colors in construction of"
            "LedPannel do not exist");
    }

    /*
     * Collect the number of rows and columns specified by the user.
     * These values are used in determining the size of led lights and the 
     * strings
     */
    mCols = mLabelVector.size();
    mRows = 0;
    uint32_t tmpMaxStringLength = 0;
    uint32_t tmpPrevMaxStringLength = 0;
    for (std::vector<std::vector<std::string> >::iterator vect_it =
        mLabelVector.begin();
        vect_it != mLabelVector.end();
        ++vect_it) {
    
        mRows = std::max(mRows, vect_it->size());
        for (std::vector<std::string>::iterator strvect_it = vect_it->begin();
            strvect_it != vect_it->end();
            ++strvect_it) {
            
            tmpPrevMaxStringLength = tmpMaxStringLength;
            tmpMaxStringLength = std::max(tmpMaxStringLength, 
                strvect_it->length());

            if (tmpMaxStringLength > tmpPrevMaxStringLength) {
                mLongestString = (*strvect_it);
            }
        } 
    }

    std::copy(mInitialColorVector.begin(), mInitialColorVector.end(), 
        std::back_inserter(mCurrentColorVector));
    setMinimumHeight(75);
    setMaximumHeight(150);
    ResizeCalculations();
}

void LedPannelGlWidget::slotSetLightColor(const uint32_t tmpRow,
    const uint32_t tmpCol, const QColor &tmpNewColor) {

    if ((tmpRow * mCols) + (tmpCol) >= mLedLightVector.size() ||
        tmpCol >= mCurrentColorVector.size()) {
        return;
    }
    mLedLightVector[tmpRow * mCols + tmpCol].setCurrentColor(tmpNewColor);
    mCurrentColorVector[tmpCol][tmpRow] = tmpNewColor;
}


void LedPannelGlWidget::GenerateContents() {
    if (!mLedLightVector.empty()) {
        mLedLightVector.clear();
    }
    if (!mLedNameStringVector.empty()) {
        mLedNameStringVector.clear();
    }

    typedef std::vector<std::vector<std::string> >::iterator VectStringIter_t;
    typedef std::vector<std::string>::iterator StringIter_t;

    uint32_t tmpCol = 0;
    float_t tmpXPos = LedHSpacing + mBubbleDiameter/2.0f;
    for (VectStringIter_t vect_it = mLabelVector.begin();
        vect_it != mLabelVector.end();
        ++vect_it) {
        uint32_t tmpRow = 0;
        float_t tmpYPos = mHeight - (LedVSpacing + mStringHeight/2.0);
        for (StringIter_t strvect_it = vect_it->begin();
            strvect_it != vect_it->end();
            ++strvect_it) {

            LedLight tmpLedLight(mCurrentColorVector[tmpCol][tmpRow],
                (tmpXPos),
                (tmpYPos),
                mBubbleDiameter);
            mLedLightVector.push_back(tmpLedLight);

            LedNameString tmpLedNameString(
                mFontSize,
                (*strvect_it),
                (tmpXPos + mBubbleDiameter/2.00f) + LedHSpacing,
                (tmpYPos - mBubbleDiameter/2.00f),
                (mStringWidth - LedHSpacing),
                (mBubbleDiameter));
            mLedNameStringVector.push_back(tmpLedNameString);

            ++tmpRow;
            tmpYPos -= (mStringHeight + LedVSpacing);
        }
        ++tmpCol;
        tmpXPos += (mBubbleDiameter + mStringWidth + LedHSpacing);
    }
}

void LedPannelGlWidget::ResizeCalculations() {
    float_t tmpVerticalDivisionHeight = 
        static_cast<float_t>(height())/
        static_cast<float_t>(mRows) - (LedVSpacing);

    float_t tmpHorizontalDivisionWidth =
        static_cast<float_t>(width())/
        static_cast<float_t>(mCols) - LedHSpacing;
    
    mBubbleDiameter = std::min((1/4.0f) * tmpHorizontalDivisionWidth, 
        tmpVerticalDivisionHeight);
    mStringHeight = tmpVerticalDivisionHeight;
    mStringWidth = (3/4.0f) * tmpHorizontalDivisionWidth;
    GenerateContents();
}

void LedPannelGlWidget::resizeGL(int width, int height) {
    ResizeCalculations();
    mWidth = width;
    mHeight = height;
}

void LedPannelGlWidget::resizeEvent(QResizeEvent *event) {
    ResizeCalculations();
    mWidth = event->size().width();
    mHeight = event->size().height();

    makeCurrent();

    float_t tmpVerticalDivisionHeight =
        static_cast<float_t>(height())/
        static_cast<float_t>(mRows) - (LedVSpacing);

    float_t tmpHorizontalDivisionWidth =
        static_cast<float_t>(width())/
        static_cast<float_t>(mCols) - (LedHSpacing);

    mBubbleDiameter = std::min((1/4.0f) * tmpHorizontalDivisionWidth,
        tmpVerticalDivisionHeight);
    mStringHeight = tmpVerticalDivisionHeight;
    mStringWidth = (3/4.0f) * tmpHorizontalDivisionWidth;

    for (std::vector<LedNameString>::iterator vect_it =
        mLedNameStringVector.begin();
        vect_it != mLedNameStringVector.end();
        ++vect_it) {

        vect_it->RegenerateGlTexture(mStringWidth, mStringHeight);
    }
}

void LedPannelGlWidget::updateGL() {
    makeCurrent();

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, mWidth, mHeight);
        glOrtho(0, mWidth, 0, mHeight, -mBubbleDiameter, mBubbleDiameter);

    glMatrixMode(GL_MODELVIEW);
        glScissor(0, 0, mWidth, mHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.92f, 0.92f, 0.92f, 1.0);

        glLoadIdentity();

    for (std::vector<LedNameString>::iterator vect_it =
        mLedNameStringVector.begin();
        vect_it != mLedNameStringVector.end();
        ++vect_it) {
    
        vect_it->RenderContents();
    }

    for (std::vector<LedLight>::iterator vect_it = mLedLightVector.begin();
        vect_it != mLedLightVector.end();
        ++vect_it) {
    
        vect_it->RenderContents();
    }
 
    swapBuffers();
}

void LedPannelGlWidget::slotReset() {
    typedef std::vector<std::vector<QColor> >::iterator 
        QColorVectorVectorIter_t;
    typedef std::vector<QColor>::iterator QColorVectorIter_t;
    uint32_t tmpIndex = 0;
    for (QColorVectorVectorIter_t vect_it = mInitialColorVector.begin();
        vect_it != mInitialColorVector.end();
        ++vect_it) {
        
        for (QColorVectorIter_t qcolorvect_it = vect_it->begin();
            qcolorvect_it != vect_it->end();
            ++qcolorvect_it) {

            mLedLightVector[tmpIndex].setCurrentColor((*qcolorvect_it));
            ++tmpIndex;
        }
    }
}

void LedPannelGlWidget::RefreshGLTextures() {
    makeCurrent();
    for (std::vector<LedNameString>::iterator vect_it =
        mLedNameStringVector.begin();
        vect_it != mLedNameStringVector.end();
        ++vect_it) {

        vect_it->RegenerateGlTexture();
    }
}
