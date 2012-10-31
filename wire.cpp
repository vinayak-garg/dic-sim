#include "wire.h"
#include <QtGui>

Wire::Wire(qreal x1, qreal y1, qreal x2, qreal y2, QColor c) :
    QGraphicsLineItem(x1, y1, x2, y2)
{
    setPen(QPen(QBrush(c), 2));
}

Wire::Wire(QPointF p1, QPointF p2, QColor c) :
    QGraphicsLineItem(p1.x(), p1.y(), p2.x(), p2.y())
{
    setPen(QPen(QBrush(c), 2));
}
