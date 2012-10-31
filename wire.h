#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>

class Wire : public QGraphicsLineItem
{
public:
    explicit Wire(qreal x1, qreal y1, qreal x2, qreal y2, QColor c = QColor());
    explicit Wire(QPointF p1, QPointF p2, QColor c = QColor());

signals:

public slots:

};

#endif // WIRE_H
