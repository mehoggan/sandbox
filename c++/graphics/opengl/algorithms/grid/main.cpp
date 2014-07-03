#include <QtGui/QApplication>

#include <boost/shared_ptr.hpp>

#include "mainwindow.h"
#include "singletontimer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow *main_window_ = new MainWindow();
    main_window_->show();
    boost::shared_ptr<Timer<20> > timer_20_millis_ = Timer<20>::Instance();
    timer_20_millis_->AddHandler(boost::bind(&MainWindow::slotTimerEvent,
        main_window_));
    return a.exec();
}
