#ifndef BREADBOARD_H
#define BREADBOARD_H

#include "cell.h"
#include "constants.h"

#include <QGraphicsItem>

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
