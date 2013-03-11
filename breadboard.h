#ifndef BREADBOARD_H
#define BREADBOARD_H

#include "cell.h"

#include <QGraphicsItem>

const int kTop = 50;
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

const int ktR1 = kTop + kOuterBorder;
const int ktR2 = 5*kBox - kBorder + kNotchGap + ktR1;
const int ktR3 = 12*kBox - 3*kBorder + kNotchGap + 2*kBusBorder + ktR1;
const int ktR4 = 17*kBox - 4*kBorder + 2*kNotchGap + 2*kBusBorder + ktR1;
const int ktR5 = 24*kBox - 6*kBorder + 2*kNotchGap + 4*kBusBorder + ktR1;
const int ktR6 = 29*kBox - 7*kBorder + 3*kNotchGap + 4*kBusBorder + ktR1;

const int kbR1 = ktR1 + 10*kBox + kNotchGap + kBusBorder - 2*kBorder;
const int kbR2 = kbR1 + 2*kBusBorder + 12*kBox + kNotchGap - 3*kBorder;

const int8_t BUS_ROW = 30;
const int8_t BUS_COL = kCols + 10;

class Breadboard : public QGraphicsItem
{
public:
    explicit Breadboard(qreal _x, qreal _y);

    static const int BB_WIDTH = 620;
    static const int BB_HEIGHT = 480;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    //void mouseMoveEvent(QMouseEvent * e);
private:
    qreal x, y;
};

#endif // BREADBOARD_H
