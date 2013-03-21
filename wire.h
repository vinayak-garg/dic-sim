#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>

class Wire : public QGraphicsLineItem
{
public:
    explicit Wire(qreal x1, qreal y1, qreal x2, qreal y2, QColor c = QColor());
    explicit Wire(QPointF p1, QPointF p2, QColor c = QColor());
    void markRedundent(bool _redundent = true)
    {
        redundent = _redundent;
    }

signals:

public slots:

private:
    bool redundent;
};

#endif // WIRE_H
