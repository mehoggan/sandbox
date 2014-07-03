#include "bargraphglwidget.h"

BarGraphGlWidget::BarGraphGlWidget(BarGraphWidget *tmpPtrParent,
    uint32_t tmpRows, ColumnDataVector_t &tmpColumnDataVector) :
    mPtrParent(tmpPtrParent),
    mRows(tmpRows),
    mColumnWidth(width()/tmpColumnDataVector.size()),
    mRowHeight(height()/mRows),
    mWidth(width()),
    mHeight(height()),
    mColumnDataVector(tmpColumnDataVector) {

    uint32_t i = 0;
    for (ColumnDataVector_t::iterator vect_it =
        mColumnDataVector.begin();
        vect_it != mColumnDataVector.end();
        ++vect_it) {

        BarGraphGl tmpBarGraphGl(
            vect_it->second,
            1 + i * mColumnWidth,
            5,
            mColumnWidth - 1,
            mHeight - 5,
            mRowHeight - 1,
            mRows,
            vect_it->first.second
        );
        mBarGraphVector.push_back(tmpBarGraphGl);
        ++i;
    }
}

void BarGraphGlWidget::UpdateOnParentResize(
    uint32_t tmpColumnWidth, uint32_t tmpRowHeight) {

    mColumnWidth = tmpColumnWidth;
    mRowHeight = tmpRowHeight;

    uint32_t i = 0;
    for (std::vector<BarGraphGl>::iterator vect_it = mBarGraphVector.begin();
        vect_it != mBarGraphVector.end(); ++vect_it) {

        vect_it->UpdateData(
            1 + i * mColumnWidth,
            5,
            mColumnWidth - 1,
            mHeight - 5,
            mRowHeight - 1);
        ++i;
    }

    i = 0;
}

void BarGraphGlWidget::RefreshGLTextures() {
    makeCurrent();
    for (std::vector<BarGraphGl>::iterator vect_it = mBarGraphVector.begin();
        vect_it != mBarGraphVector.end(); ++vect_it) {

        vect_it->RefreshGLTextures();
    }
}

void BarGraphGlWidget::resizeGL(int width, int height) {
    mWidth = width;
    mHeight = height;
    mColumnWidth = width/mColumnDataVector.size();
    mRowHeight = height/mRows;
    UpdateOnParentResize(mColumnWidth, mRowHeight);
}

void BarGraphGlWidget::resizeEvent(QResizeEvent *event) {
    mWidth = event->size().width();
    mHeight = event->size().height();
    mColumnWidth = mWidth/mColumnDataVector.size();
    mRowHeight = mHeight/mRows;
    UpdateOnParentResize(mColumnWidth, mRowHeight);
}

void BarGraphGlWidget::updateGL() {
    makeCurrent();

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, mWidth, mHeight);
        glOrtho(0, mWidth, 0, mHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
        glScissor(0, 0, mWidth, mHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.92f, 0.92f, 0.92f, 1.0);

        glLoadIdentity();

    for (std::vector<BarGraphGl>::iterator vect_it = mBarGraphVector.begin();
        vect_it != mBarGraphVector.end(); ++vect_it) {

        vect_it->RenderContents();
    }
    swapBuffers();
}


void BarGraphGlWidget::setBarColor(const uint32_t tmpCol,
    const QColor &tmpNewColor) {

    if (tmpCol < mBarGraphVector.size()) {
        mBarGraphVector[tmpCol].setBarColor(tmpNewColor);
    }
}

void BarGraphGlWidget::setBarValue(const uint32_t tmpCol,
    const int32_t tmpNewBarValue) {

    if (tmpCol < mBarGraphVector.size()) {
        mBarGraphVector[tmpCol].setBarValue(tmpNewBarValue);
    }
}
