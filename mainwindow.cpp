#include "mainwindow.h"

#include <QtGui>
#include <QApplication>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /****************** Menu Bar ******************/
    QAction *newAction = new QAction("&New File", this);
    newAction->setShortcut(tr("Ctrl+N"));
    QAction *quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(tr("Ctrl+Q"));

    QMenu *fileMenu;
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(quitAction);

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QAction *aboutAction = new QAction("&About", this);

    QMenu *helpMenu;
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);

    /*************** Central Contents ***************/
    /*
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background, *(new QBrush( *(new QPixmap("images/textures/icobbg1.png")))));
    setPalette(*palette);
    */

    setStyleSheet("background-image: url(images/textures/icobbg1.png);");
}

MainWindow::~MainWindow()
{
    
}
