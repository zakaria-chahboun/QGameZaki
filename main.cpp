#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

    QImage im("://Res/TIMER.jpg");
    im = im.scaled(800,800,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    QSplashScreen splash(QPixmap::fromImage(im));
    splash.show();

    MainWindow w;
    QTimer::singleShot(2500, &splash,SLOT(close())); // Timer
    QTimer::singleShot(2500,&w,SLOT(showMaximized()));

    return a.exec();
}
