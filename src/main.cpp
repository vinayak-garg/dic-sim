#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include "mainwindow.h"
#include "led.h"
#include "cell.h"
#include "inputcell.h"
#include "powerbutton.h"
#include "togglebutton.h"
#include "block.h"
#include "constants.h"

int main(int argc, char *argv[])
{
    int WIDTH = 900;
    int HEIGHT = 650;

    int screenWidth;
    int screenHeight;

    int x, y;

    QApplication a(argc, argv);

    LED::initLed();
    Cell::initCell();
    InputCell::init();
    PowerButton::init();
    ToggleButton::initToggleButton();
    Block::init();

    MainWindow window;
    window.setWindowTitle(QString("DIC Sim v") + VERSION);

    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;

    window.resize(WIDTH, HEIGHT);
    window.move(x, y);

    window.setStyleSheet(
        "QWidget #centralWidget{background-image : url(:/bg/images/textures/bg1.png);}"
        "QWidget #breadboard{background : #fefcfa; border-radius : 10px}"
        "QGraphicsView{background : #a3a0a0; border-radius : 8px}"
    );

    window.show();
    
    return a.exec();
}
