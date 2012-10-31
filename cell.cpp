#include "cell.h"

Cell::Cell(qreal x, qreal y, qreal w, qreal h)
    : QGraphicsRectItem(0, 0, w, h)
{
    setAcceptHoverEvents(true);
    cellColor.setRgb(180, 180, 180);
    highlightColor.setRgb(0, 180, 0);
    setBrush(cellColor);
    setPos(x, y);
}
/*
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QMessageBox::information(0, "You clicked!", "Oh my god you clicked!");
}
*/
