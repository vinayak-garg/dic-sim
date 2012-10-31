#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>
#include <QtGui>

class Cell : public QGraphicsRectItem
{
public:
    Cell(qreal x, qreal y, qreal w, qreal h);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *)
    {
        setBrush(highlightColor);
        update();
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *)
    {
        setBrush(cellColor);
        update();
    }
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor cellColor;
    QColor highlightColor;
};

#endif // CELL_H
