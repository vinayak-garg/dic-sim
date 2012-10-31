#include "breadboard.h"
#include "cell.h"
#include "wire.h"

#include <QtGui>

//const int BB_WIDTH = 620;
//const int BB_HEIGHT = 480;

Breadboard::Breadboard(QWidget *parent) :
    QGraphicsScene(0, 0, BB_WIDTH, BB_HEIGHT, parent)
{

    //Initialisation
    mode = first;

    //setFixedSize(BB_WIDTH, BB_HEIGHT);

    highlightColor.setRgb(0, 200, 0);
    selectedTColor.setRgb(255, 200, 0);
    selectedBColor.setRgb(240, 200, 0);
    terminalColor.setRgb(180, 180, 180);
    //busColor.setRgb(185, 185, 185);
    borderColor.setRgb(80, 80, 80);
    backgroundColor.setRgb(254, 252, 250);

    const int x1 = kOuterBorder - 2,        //-2 for slight adjustment
        x2 = x1 + kCols*kBox - kBorder + 2;
    int x = kOuterBorder, y, i, j;

    for(i = 0; i < kCols; x+=kBox, i++)
    {
        for(j = 0; j < 5; j++)
        {
            addItem(new Cell(x, ktR1 + j*kBox, kSquare, kSquare));

            addItem(new Cell(x, ktR2 + j*kBox, kSquare, kSquare));

            addItem(new Cell(x, ktR3 + j*kBox, kSquare, kSquare));
            addItem(new Cell(x, ktR4 + j*kBox, kSquare, kSquare));

            addItem(new Cell(x, ktR5 + j*kBox, kSquare, kSquare));
            addItem(new Cell(x, ktR6 + j*kBox, kSquare, kSquare));
        }
    }

    //Bus Contacts
    y = kOuterBorder + 10*kBox + kNotchGap + kBusBorder - 2*kBorder;
    for (i = 0, x = kOuterBorder; i < kBusCols; x+=kBusGap, i++)
    {
        for (j = 0; j < 5; x+=kBox, j++)
        {
            addItem(new Cell(x, kbR1, kSquare, kSquare));
            addItem(new Cell(x, kbR1 + kBox, kSquare, kSquare));
            addItem(new Cell(x, kbR2, kSquare, kSquare));
            addItem(new Cell(x, kbR2 + kBox, kSquare, kSquare));
        }
    }

    //Bus Lines
    addLine(x1, y - 6, x2, y - 6, QPen(QBrush(Qt::red), 2));
    addLine(x1, y + 2*kBusBorder + 12*kBox + kNotchGap - 3*kBorder - 6,
            x2, y + 2*kBusBorder + 12*kBox + kNotchGap - 3*kBorder - 6, QPen(QBrush(Qt::red), 2));
    addLine(x1, y + 2*kBox - kBorder + 6, x2, y + 2*kBox - kBorder + 6, QPen(QBrush(Qt::blue), 2));
    addLine(x1, y + 2*kBusBorder + 14*kBox + kNotchGap - 4*kBorder + 6,
            x2, y + 2*kBusBorder + 14*kBox + kNotchGap - 4*kBorder + 6, QPen(QBrush(Qt::blue), 2));

    //Notch
    y = kOuterBorder + 5*kBox - kBorder + (kNotchGap>>1);
    addLine(x1, y, x2, y, QPen(QBrush(Qt::gray), 5));
    y += 12*kBox - 3*kBorder + 2*kBusBorder + kNotchGap;
    addLine(x1, y, x2, y, QPen(QBrush(Qt::gray), 5));
    y += 12*kBox - 3*kBorder + 2*kBusBorder + kNotchGap;
    addLine(x1, y, x2, y, QPen(QBrush(Qt::gray), 5));
}

void Breadboard::setWireColor(QColor color)
{
    wireColor = color;
}

void Breadboard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Cell * topItem = dynamic_cast<Cell *>(itemAt(event->scenePos()));
    if (topItem)
    {
        topItem->setBrush(Qt::yellow);
        QPointF mousePos(topItem->scenePos().x() + (kSquare>>1), topItem->pos().y() + (kSquare>>1));

        if (mode == second)
        {
            addItem(new Wire(lastMousePos, mousePos, wireColor));
            mode = first;
        }
        else
        {
            lastMousePos = mousePos;
            lastRect = topItem;
            mode = second;
        }
    }
}
