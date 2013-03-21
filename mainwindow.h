#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "console.h"
#include "icdialog.h"
#include "blockdata.h"
#include "circuit.h"

#include <memory>

#include <QtGui>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void actionNew();
    void actionOpen();
    void actionSave();
    void actionRunCircuit();
    void actionStopCircuit();
    void actionAbout();
    void actionChooseWireColor();
    void actionInsertWire()
    {
        console->setMode(Mode::inserting_wire);
    }
    void actionInsertLED()
    {
        console->setMode(Mode::inserting_led);
    }
    void actionInsertIC();

    void circuitPowerToggled();

protected:
    void parseICs();

private:
    QGraphicsView *consoleView;
    Console *console;
    ICDialog *icdialog;
    std::vector<std::vector<BlockData> > ICDataList;
    QList<short> icPinNumList;
    std::unique_ptr<Circuit> circuit;
    bool circuitState;
};

#endif // MAINWINDOW_H
