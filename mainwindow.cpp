#include "mainwindow.h"
#include "console.h"

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

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *fileMenu;
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(quitAction);

    QAction *undoAction = new QAction("&Undo", this);
    undoAction->setShortcut(tr("Ctrl+Z"));
    QAction *redoAction = new QAction("&Redo", this);
    redoAction->setShortcut(tr("Ctrl+Y"));

    QMenu *editMenu;
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    QAction *aboutAction = new QAction("&About", this);

    connect(aboutAction, SIGNAL(triggered()), this, SLOT(actionAbout()));

    QMenu *helpMenu;
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);

    /*************** Central Contents ***************/

    QWidget *centralWidget = new QWidget;
    centralWidget->setObjectName(QObject::tr("centralWidget"));

    console = new Console;
    console->setObjectName(QObject::tr("console"));

    QVBoxLayout *vLayout = new QVBoxLayout;

    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout->addStretch(1);
    hLayout->addWidget(console);
    hLayout->addStretch(1);

    vLayout->addStretch(1);
    vLayout->addLayout(hLayout);
    vLayout->addStretch(1);

    centralWidget->setLayout(vLayout);

    //centralWidget->setStyleSheet("QWidget #centralWidget{background-image : url(:/it/images/textures/icobbg1.png);}");
    //if (QFile::exists(":/it/images/textures/icobbg1.png"))
      //  actionAbout();

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete console;
}

void MainWindow::actionAbout()
{
    QMessageBox::information(this, "About DIC Sim", "DIC Sim is a simulator for prototyping circuits built using Digital ICs.<br/>Author : Vinayak Garg<br/>Version : 0.1");
}
