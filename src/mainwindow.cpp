#include "mainwindow.h"
#include "console.h"
#include "iclexer.h"
#include "icparser.h"
#include "icdialog.h"
#include "icviewer.h"
#include "blockdata.h"

#include <fstream>
#include <vector>

#include <QtGui>
#include <QtDebug>

std::ifstream *infile;

QStringList *icNameList;
QStringList *icPinsList;
QStringList *icDescList;
QStringList *icLabelList;

std::vector<BlockData> ICData;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /****************** Menu Bar ******************/
    /*
     * File Menu
     */
    QAction *newAction = new QAction("&New File", this);
    newAction->setShortcut(tr("Ctrl+N"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(actionNew()));
    QAction *openAction = new QAction("&Open File", this);
    openAction->setShortcut(tr("Ctrl+O"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(actionOpen()));
    QAction *saveAction = new QAction("&Save File", this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(actionSave()));
    QAction *quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *fileMenu;
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(quitAction);

    /*
     * Edit Menu
     */
    QAction *undoAction = new QAction("&Undo", this);
    undoAction->setShortcut(tr("Ctrl+Z"));

    QAction *redoAction = new QAction("&Redo", this);
    redoAction->setShortcut(tr("Ctrl+Y"));

    QAction *chooseWireColorAction = new QAction("Choose Wire &Color", this);
    chooseWireColorAction->setShortcut(tr("Ctrl+C"));
    connect(chooseWireColorAction, SIGNAL(triggered()), this, SLOT(actionChooseWireColor()));

    QMenu *editMenu;
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(chooseWireColorAction);

    /*
     * Insert Menu
     */
    QAction *insertWireAction = new QAction("Insert &Wire", this);
    insertWireAction->setShortcut(tr("Ctrl+W"));
    connect(insertWireAction, SIGNAL(triggered()), this, SLOT(actionInsertWire()));

    QAction *insertLEDAction = new QAction("Insert &LED", this);
    insertLEDAction->setShortcut(tr("Ctrl+L"));
    connect(insertLEDAction, SIGNAL(triggered()), this, SLOT(actionInsertLED()));

    QAction *insertICAction = new QAction("Insert &IC", this);
    insertICAction->setShortcut(tr("Ctrl+I"));
    connect(insertICAction, SIGNAL(triggered()), this, SLOT(actionInsertIC()));

    QMenu *insertMenu;
    insertMenu = menuBar()->addMenu("&Insert");
    insertMenu->addAction(insertWireAction);
    insertMenu->addAction(insertLEDAction);
    insertMenu->addAction(insertICAction);

    /*
     * Circuit Menu
     */
    QAction *runCircuitAction = new QAction("&Run Circuit", this);
    runCircuitAction->setShortcut(tr("F5"));
    connect(runCircuitAction, SIGNAL(triggered()), this, SLOT(actionRunCircuit()));
    QAction *stopCircuitAction = new QAction("&Stop Circuit", this);
    stopCircuitAction->setShortcut(tr("F12"));
    connect(stopCircuitAction, SIGNAL(triggered()), this, SLOT(actionStopCircuit()));

    QMenu *circuitMenu;
    circuitMenu = menuBar()->addMenu("&Circuit");
    circuitMenu->addAction(runCircuitAction);
    circuitMenu->addAction(stopCircuitAction);

    /*
     * Help Menu
     */
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
    consoleView = new QGraphicsView(console);
    consoleView->setFixedSize(Console::CONSOLE_WIDTH, Console::CONSOLE_HEIGHT);
    connect(console, SIGNAL(powerToggled()), this, SLOT(circuitPowerToggled()));

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout->addStretch(1);
    hLayout->addWidget(consoleView);
    hLayout->addStretch(1);

    vLayout->addStretch(1);
    vLayout->addLayout(hLayout);
    vLayout->addStretch(1);

    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);

    /************* Containers ****************/
    icNameList = new QStringList;
    icPinsList = new QStringList;
    icDescList = new QStringList;
    icLabelList = new QStringList;

    /************ Functions ******************/
    parseICs();
    icdialog = new ICDialog(this, icNameList, icDescList);

    /************ Booleans *******************/
    circuitState = false;
}

MainWindow::~MainWindow()
{
    delete console;
}

void MainWindow::actionNew()
{
    delete console;
    console = new Console;
    console->setObjectName(QObject::tr("console"));
    consoleView->setScene(console);
}

void MainWindow::actionOpen()
{
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open Circuit"), "",
                                         tr("Digital Circuit (*.dic);;All Files (*)"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_7);

        actionNew();
        in >> *console;
        connect(console, SIGNAL(powerToggled()), this, SLOT(circuitPowerToggled()));
    }
}

void MainWindow::actionSave()
{
    QString fileName =
            QFileDialog::getSaveFileName(this, tr("Save Circuit"), "",
                                         tr("Digital Circuit (*.dic);;All Files (*)"));
    if (!fileName.isEmpty())
    {
        if (!fileName.endsWith(".dic"))
            fileName.append(".dic");
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to save file"),
                                     file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_7);
        out << *console;
    }
}

void MainWindow::actionRunCircuit()
{
    if (!circuitState)
    {
        console->togglePower();
        circuit.reset(new Circuit(console));
        circuit->prepareConnections();
        circuit->run();
        circuitState = true;
    }
}

void MainWindow::actionStopCircuit()
{
    if (circuitState)
    {
        console->togglePower();
        circuit->stop();
        circuitState = false;
    }
}

void MainWindow::actionAbout()
{
    QMessageBox::information(this, "About DIC Sim",
        "DIC Sim is a simulator for prototyping circuits built using Digital ICs."
        "<br/>Author : Vinayak Garg<br/>Version : 0.1.5");
}

void MainWindow::actionChooseWireColor()
{
    QColor c = QColorDialog::getColor(Qt::black);
    if (c.isValid())
    {
        console->setWireColor(c);
    }
}

void MainWindow::actionInsertIC()
{
    if (icdialog->exec() == QDialog::Accepted)
    {
        int index = icdialog->getIndex();
        ICViewer *icv = new ICViewer(this, icNameList->at(index),
                                     icLabelList->at(index));
        icv->show();
        console->setMode(Mode::inserting_ic);
        console->setIC(icNameList->at(index), icPinNumList[index],
                       ICDataList[index]);
    }
}

void MainWindow::circuitPowerToggled()
{
    if (circuitState) //Circuit Running
        actionStopCircuit();
    else
        actionRunCircuit();
}

void MainWindow::parseICs()
{
    QDir dir("icdata", "*.ic");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    QFileInfoList filelist = dir.entryInfoList();
    for (int i = 0; i < filelist.size(); ++i)
    {
        ICData.clear();
        QFileInfo fileInfo = filelist.at(i);
        //icNameList->append(fileInfo.baseName());
        QByteArray ba = fileInfo.filePath().toLocal8Bit();
        infile = new std::ifstream(ba.data());
        initLexer(infile);

        Parser p;
        p.parse();

        infile->close();
        delete infile;
/*
        for (auto it = ICData.begin(); it != ICData.end(); it++)
        {
            qDebug() << it->id << ' ' << it->inPin[0] << ','
                     << it->outPin.size();
        }
*/
        ICDataList.push_back(std::move(ICData));
    }

    //Clean description list
    for (auto it = icNameList->begin(); it != icNameList->end(); ++it)
    {
        QString &s = *it;
        s.chop(1);
        s.remove(0, 1);
    }
    for (auto it = icPinsList->begin(); it != icPinsList->end(); ++it)
    {
        QString s = *it;
        s.chop(1);
        s.remove(0, 1);
        icPinNumList.append(s.toShort());
    }
    icPinsList->clear();
    for (auto it = icDescList->begin(); it != icDescList->end(); ++it)
    {
        QString &s = *it;
        s.chop(1);
        s.remove(0, 1);
    }
    for (auto it = icLabelList->begin(); it != icLabelList->end(); ++it)
    {
        QString &s = *it;
        s.chop(1);
        s.remove(0, 1);
    }
}
