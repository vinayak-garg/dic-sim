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
    MainWindow window;
    window.setWindowTitle("DIC Sim");

    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;

    window.resize(WIDTH, HEIGHT);
    window.move(x, y);

    window.setStyleSheet(
                "QWidget #centralWidget{background-image : url(:/bg/images/textures/bg1.png);}"
                "QWidget #console{background : #006600}"
                "QWidget #breadboard{background : #fefcfa; border-radius : 10px}"
                );

    window.show();
    
    return a.exec();
}
