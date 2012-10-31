#ifndef BREADBOARD_H
#define BREADBOARD_H

#include "cell.h"

#include <QGraphicsScene>
//#include <QMouseEvent>

const int kTop = 40;
const int kLeft = 30;
const int kWidth = 620;
const int kHeight = 480;
const int kRadius = 15;
const int kBorder = 4;
const int kSquare = 6;
const int kBox = kBorder + kSquare;
const int kOuterBorder = 16;
const int kCols = 59;
const int kNotchGap = 2*kBox;
const int kBusBorder = 2*kBox;
const int kBusGap = kBox;
const int kBusCols = 10;

const int ktR1 = kOuterBorder;
const int ktR2 = 5*kBox - kBorder + kNotchGap + kOuterBorder;
const int ktR3 = 12*kBox - 3*kBorder + kNotchGap + 2*kBusBorder + kOuterBorder;
const int ktR4 = 17*kBox - 4*kBorder + 2*kNotchGap + 2*kBusBorder + kOuterBorder;
const int ktR5 = 24*kBox - 6*kBorder + 2*kNotchGap + 4*kBusBorder + kOuterBorder;
const int ktR6 = 29*kBox - 7*kBorder + 3*kNotchGap + 4*kBusBorder + kOuterBorder;

const int kbR1 = kOuterBorder + 10*kBox + kNotchGap + kBusBorder - 2*kBorder;
const int kbR2 = kbR1 + 2*kBusBorder + 12*kBox + kNotchGap - 3*kBorder;

enum ContactStatus
{
    kUndefined,
    kTerminal,
    kBus,
    kTSelected, //terminal selected
    kBSelected,
    kOutside
};

enum Groups
{
    kTerminal1,
    kTerminal2,
    kTerminal3,
    kTerminal4,
    kTerminal5,
    kTerminal6,
    kBus1,
    kBus2
};

enum Mode
{
    first,
    second
};

struct Contact
{
    Groups group;
    short row;
    short col;
    //wxPoint center;
    void set(Groups _group, short _row, short _col)//, wxPoint _center)
    {
        group = _group;
        row = _row;
        col = _col;
        //center = _center;
    }
};

class Breadboard : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Breadboard(QWidget *parent = 0);

    static const int BB_WIDTH = 620;
    static const int BB_HEIGHT = 480;

    void setWireColor(QColor);
signals:
    
public slots:

protected:
    //void paintEvent(QPaintEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent * e);

private:

    Mode mode;

    QPointF lastMousePos;
    Cell *lastRect;

    QColor highlightColor;
    QColor selectedTColor;
    QColor selectedBColor;
    QColor terminalColor;
    QColor busColor;
    QColor borderColor;
    QColor backgroundColor;

    QColor wireColor;
};

#endif // BREADBOARD_H
