#ifndef INPUTCELL_H
#define INPUTCELL_H

#include "constants.h"

#include <QtGui>

class InputCell : public QGraphicsEllipseItem
{
public:
    InputCell(qreal x, qreal y, qreal w, qreal h, int r, int c);
    void occupy()
    {
        occupied = true;
        setBrush(occupiedCellColor);
        update();
    }
    void unoccupy()
    {
        occupied = false;
        setBrush(cellColor);
        update();
    }
    bool isOccupied()
    {
        return occupied;
    }
    bool isCenter()
    {
        return ((m_r+1)%5 == 0 && (m_r+1)%10); //true for 4, 14, 24
    }
    int index()
    {
        return (m_r/5)*kCols + m_c;
    }

    int row()
    {
        return m_r;
    }
    int col()
    {
        return m_c;
    }

    static void init();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *)
    {
        if (isOccupied())
            setBrush(occupiedHighlightColor);
        else
            setBrush(highlightColor);
        update();
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *)
    {
        if (isOccupied())
            setBrush(occupiedCellColor);
        else
            setBrush(cellColor);
        update();
    }

private:
    static QColor cellColor;
    static QColor highlightColor;
    static QColor occupiedCellColor;
    static QColor occupiedHighlightColor;
    bool occupied;
    int m_r, m_c;
};

#endif // INPUTCELL_H
