#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    int WIDTH = 900;
    int HEIGHT = 650;

    int screenWidth;
    int screenHeight;

    int x, y;

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("DIC Sim");

    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;

    w.resize(WIDTH, HEIGHT);
    w.move(x, y);

    w.show();
    
    return a.exec();
}
