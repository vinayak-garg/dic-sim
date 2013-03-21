#include "breadboard.h"
#include "cell.h"
#include "wire.h"

#include <QtGui>

Breadboard::Breadboard(qreal _x, qreal _y)
    : x(_x), y(_y)
{
    setZValue(-3);
}

QRectF Breadboard::boundingRect() const
{
    qreal pw = 2;
    return QRectF(x - pw/2, y - pw/2, BB_WIDTH + pw, BB_HEIGHT + pw);
}

void Breadboard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QBrush(Qt::white));
    painter->drawRoundedRect(x, y, BB_WIDTH, BB_HEIGHT, 10, 10);

    const int x1 = kOuterBorder + kLeft,
        x2 = x1 + kCols*kBox - kBorder + 2;
    int y = kTop + kOuterBorder + 10*kBox + kNotchGap + kBusBorder - 2*kBorder;

    //Bus Lines
    painter->setPen(QPen(QBrush(Qt::red), 2));
    painter->drawLine(x1, y - 6, x2, y - 6);
    painter->drawLine(x1, y + 2*kBusBorder + 12*kBox + kNotchGap - 3*kBorder - 6,
            x2, y + 2*kBusBorder + 12*kBox + kNotchGap - 3*kBorder - 6);
    painter->setPen(QPen(QBrush(Qt::blue), 2));
    painter->drawLine(x1, y + 2*kBox - kBorder + 6, x2, y + 2*kBox - kBorder + 6);
    painter->drawLine(x1, y + 2*kBusBorder + 14*kBox + kNotchGap - 4*kBorder + 6,
            x2, y + 2*kBusBorder + 14*kBox + kNotchGap - 4*kBorder + 6);
    //Notch
    painter->setPen(QPen(QBrush(Qt::gray), 5));
    y = kOuterBorder + kTop + 5*kBox - kBorder + (kNotchGap>>1);
    painter->drawLine(x1, y, x2, y);
    y += 12*kBox - 3*kBorder + 2*kBusBorder + kNotchGap;
    painter->drawLine(x1, y, x2, y);
    y += 12*kBox - 3*kBorder + 2*kBusBorder + kNotchGap;
    painter->drawLine(x1, y, x2, y);
}
