#include "mainwindow.h"

#include <QApplication>
#include <QAction>
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QAction *newAction = new QAction("&New File", this);
    QAction *quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(tr("Ctrl+Q"));

    QMenu *fileMenu;
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(quitAction);

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    
}
