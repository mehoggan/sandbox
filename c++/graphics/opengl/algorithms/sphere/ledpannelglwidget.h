#ifndef LEDPANNELGLWIDGET_H
#define LEDPANNELGLWIDGET_H

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
#include "ledlight.h"
#include "lednamestring.h"

class LedPannelGlWidget : public QGLWidget {
    Q_OBJECT
private:
    enum LedSpecs { LedVSpacing = 10, LedHSpacing = 10, LedMaxFontSize = 48 };

    std::vector<std::vector<std::string> > mLabelVector;
    std::vector<std::vector<QColor> > mInitialColorVector;
    std::vector<std::vector<QColor> > mCurrentColorVector;
    uint32_t mRows;
    uint32_t mCols;
    uint32_t mWidth;
    uint32_t mHeight;
    uint32_t mFontSize;
    float_t mBubbleDiameter;
    float_t mStringHeight;
    float_t mStringWidth;
    std::string mLongestString;

    std::vector<LedLight> mLedLightVector;
    std::vector<LedNameString> mLedNameStringVector;

    void GenerateContents();
    void ResizeCalculations();

    LedPannelGlWidget(const LedPannelGlWidget &other);   
    LedPannelGlWidget &operator=(const LedPannelGlWidget &other);

protected:
    virtual void resizeGL(int width, int height);
    virtual void resizeEvent(QResizeEvent *event);

public:
    LedPannelGlWidget(
        uint32_t tmpFontSize,
        std::vector<std::vector<std::string> > &tmpLabelVector,
        std::vector<std::vector<QColor> > &tmpInitialColorVector);
    void RefreshGLTextures();
    
public slots:
    virtual void updateGL();
    void slotReset();
    void slotSetLightColor(const uint32_t tmpRow, const uint32_t tmpCol, 
        const QColor &tmpNewColor);

};

#endif //LEDPANNELGLWIDGET_H
