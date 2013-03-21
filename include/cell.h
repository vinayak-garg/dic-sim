#ifndef CELL_H
#define CELL_H

#include <QtGui>

constexpr int terminalCell()
{
    return 1 << 16;
}
constexpr int highVoltageCell()
{
    return 1 << 17;
}
constexpr int centerCell()
{
    return 1 << 18;
}

class Cell : public QGraphicsRectItem
{
public:
    Cell(qreal x, qreal y, qreal w, qreal h, int8_t r, int8_t c, int _id = 0);
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
        return id & centerCell();
    }
    int8_t row()
    {
        return m_r;
    }
    int8_t col()
    {
        return m_c;
    }

    static void initCell();

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
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    static QColor cellColor;
    static QColor highlightColor;
    static QColor occupiedCellColor;
    static QColor occupiedHighlightColor;
    bool occupied;
    int8_t m_r, m_c;
    const int id;
};

#endif // CELL_H
