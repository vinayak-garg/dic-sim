#include "inputcell.h"

QColor InputCell::cellColor;
QColor InputCell::highlightColor;
QColor InputCell::occupiedCellColor;
QColor InputCell::occupiedHighlightColor;

InputCell::InputCell(qreal x, qreal y, qreal w, qreal h, int r, int c)
    : QGraphicsEllipseItem(0, 0, w, h), m_r(r), m_c(c)
{
    setAcceptHoverEvents(true);
    setBrush(cellColor);
    setPos(x, y);
    unoccupy();
    setZValue(-2);
}

void InputCell::init()
{
    cellColor.setRgb(90, 90, 90);
    highlightColor.setRgb(0, 210, 0);
    occupiedCellColor.setRgb(105, 105, 105);
    occupiedHighlightColor.setRgb(240, 0, 0);
}
