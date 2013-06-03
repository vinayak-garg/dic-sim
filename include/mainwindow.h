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
    void actionTruthTable();
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
    void actionInsertTag();

    void actionToggleInput(int i)
    {
        console->toggleInput(i);
        consoleInputToggled();
    }
    void actionToggleInput1() {actionToggleInput(0);}
    void actionToggleInput2() {actionToggleInput(1);}
    void actionToggleInput3() {actionToggleInput(2);}
    void actionToggleInput4() {actionToggleInput(3);}
    void actionToggleInput5() {actionToggleInput(4);}
    void actionToggleInput6() {actionToggleInput(5);}
    void actionToggleInput7() {actionToggleInput(6);}
    void actionToggleInput8() {actionToggleInput(7);}
    void actionToggleInput9() {actionToggleInput(8);}
    void actionToggleInput0() {actionToggleInput(9);}

    void actionCheatNO_GND_VCC()
    {
        cheatNO_GND_VCC = !cheatNO_GND_VCC;
    }

    void consolePowerToggled();
    void consoleInputToggled();

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
    bool cheatNO_GND_VCC;
};

#endif // MAINWINDOW_H
