#include "cell.h"

QColor Cell::cellColor;
QColor Cell::highlightColor;
QColor Cell::occupiedCellColor;
QColor Cell::occupiedHighlightColor;

Cell::Cell(qreal x, qreal y, qreal w, qreal h, int r, int c, int _id)
    : QGraphicsRectItem(0, 0, w, h), m_r(r), m_c(c), id(_id)
{
    setAcceptHoverEvents(true);
    setBrush(cellColor);
    setPos(x, y);
    unoccupy();
    setZValue(-2);
}

void Cell::initCell()
{
    cellColor.setRgb(180, 180, 180);
    highlightColor.setRgb(0, 210, 0);
    occupiedCellColor.setRgb(105, 105, 105);
    occupiedHighlightColor.setRgb(240, 0, 0);
}
