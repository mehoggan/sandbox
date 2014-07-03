#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    glwidget1_ptr_ = new GLWidget(this, NULL);
    glwidget2_ptr_ = new GLWidget(this, glwidget1_ptr_);

    assert(glwidget1_ptr_->isSharing() && "Not sharing");

    main_hbox_layout_ptr_ = new QHBoxLayout();
    center_widget_ptr_ = new QWidget(this);
    setCentralWidget(center_widget_ptr_);
    center_widget_ptr_->setLayout(main_hbox_layout_ptr_);

    main_hbox_layout_ptr_->addWidget(glwidget1_ptr_);
    main_hbox_layout_ptr_->addWidget(glwidget2_ptr_);

    connect(this, SIGNAL(signalTimerEvent()),
        this, SLOT(slotRender()));
    resize(1020, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotRender() {
    const_cast<QGLContext *>(glwidget1_ptr_->context())->makeCurrent();
    glwidget1_ptr_->updateGL();
    const_cast<QGLContext *>(glwidget1_ptr_->context())->swapBuffers();
    const_cast<QGLContext *>(glwidget2_ptr_->context())->makeCurrent();
    glwidget2_ptr_->updateGL();
    const_cast<QGLContext *>(glwidget2_ptr_->context())->swapBuffers();
}

void MainWindow::slotTimerEvent() {
    emit signalTimerEvent();
}
