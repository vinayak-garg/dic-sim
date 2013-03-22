#include "ic.h"
#include "breadboard.h"

static const int kPinHeight = 4;

IC::IC(QString _name, int _l, QPointF _pos, int _index,
       std::vector<BlockData> _blocks) :
    name(_name), l(_l), blocks(_blocks), index(_index)
{
    x = _pos.x() - 4;
    y = _pos.y();
    setZValue(-1);
}

QRectF IC::boundingRect() const
{
    return QRectF(x - 1, y - 1, l*kBox + 1, 2*(kBox + kPinHeight) + 1);
}

void IC::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush b(Qt::black);
    painter->fillRect(x, y + kPinHeight, l*kBox, 2*kBox, b);
    b.setColor(Qt::lightGray);
    QFontMetrics fm = painter->fontMetrics();
    painter->drawText(x + 5, y + 2 + fm.height(), name);
    b.setColor(Qt::yellow);
    for (int i = 0; i < l; ++i)
    {
        painter->fillRect(x + kBorder/2 + i*kBox, y, kSquare-1, kPinHeight, b);
        painter->fillRect(x + kBorder/2 + i*kBox,
                          y + kPinHeight + 2*kBox, kSquare-1, kPinHeight, b);
    }
}
