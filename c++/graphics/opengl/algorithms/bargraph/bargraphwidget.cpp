#include "bargraphwidget.h"

BarGraphWidget::BarGraphWidget(uint32_t tmpRows, 
    ColumnDataVector_t tmpColumnDataVector) :
    mWidth(width()),
    mHeight(height()),
    mColumnDataVector(tmpColumnDataVector),
    mCols(tmpColumnDataVector.size()),
    mRows(tmpRows),
    mPtrBarGraphGlWidget(NULL) {

    if (mRows == 0) {
        throw std::runtime_error("You cannot build a bar graph with 0 bars");
    }

    ResizeCalculations();

    mPtrMainVBoxLayout = new QVBoxLayout(this);
    mPtrQLabelHBoxLayout = new QHBoxLayout();
    mPtrMainVBoxLayout->addLayout(mPtrQLabelHBoxLayout);

    for (ColumnDataVector_t::iterator vect_it = mColumnDataVector.begin();
        vect_it != mColumnDataVector.end();
        ++vect_it) {

        QLabel *tmpPtrQLabel = new QLabel(vect_it->first.first);
        tmpPtrQLabel->setSizePolicy(QSizePolicy::Maximum,
            QSizePolicy::Minimum);
        tmpPtrQLabel->setMaximumHeight(50);
        tmpPtrQLabel->setFont(QFont("Arial", 6));
        tmpPtrQLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //tmpPtrQLabel->resize(mColumnWidth, mRowHeight);
        mColumnQLabelVector.push_back(tmpPtrQLabel);
        mPtrQLabelHBoxLayout->addWidget(mColumnQLabelVector.back());
    }

    mPtrBarGraphGlWidget = new BarGraphGlWidget(
        this, mRows + 1,  mColumnDataVector);
    mPtrBarGraphGlWidget->setMaximumHeight(400);
    mPtrMainVBoxLayout->addWidget(mPtrBarGraphGlWidget);

    setLayout(mPtrMainVBoxLayout);
    setMinimumSize(100, 100);
}

BarGraphWidget::~BarGraphWidget() {
}

void BarGraphWidget::ResizeCalculations() {
    mColumnWidth = (width())/mCols;
    mRowHeight = (height())/mRows;
}

void BarGraphWidget::RefreshGLTextures() {
    mPtrBarGraphGlWidget->RefreshGLTextures();
}

void BarGraphWidget::setBarColor(const uint32_t tmpCol, 
    const QColor &tmpNewColor) {

    mPtrBarGraphGlWidget->setBarColor(tmpCol, tmpNewColor);
}

void BarGraphWidget::setBarValue(const uint32_t tmpCol,
    const int32_t tmpNewBarValue) {

    mPtrBarGraphGlWidget->setBarValue(tmpCol, tmpNewBarValue);
}

void BarGraphWidget::resizeEvent(QResizeEvent *event) {
    ResizeCalculations();
    mWidth = event->size().width();
    mHeight = event->size().height();
}

void BarGraphWidget::slotTimerUpdateRequest() {
    mPtrBarGraphGlWidget->updateGL();
}
