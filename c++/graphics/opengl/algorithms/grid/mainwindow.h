#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QTimer>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <QtOpenGL/QGLContext>

#include <stdexcept>
#include <assert.h>

#include "glwidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void signalTimerEvent();

private:
    QWidget *center_widget_ptr_;
    GLWidget *glwidget1_ptr_;
    GLWidget *glwidget2_ptr_;
    QHBoxLayout *main_hbox_layout_ptr_;

    QTimer *render_timer_ptr_;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotRender();
    void slotTimerEvent();
};

#endif // MAINWINDOW_H
