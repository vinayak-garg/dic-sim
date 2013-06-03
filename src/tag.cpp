#include "tag.h"

Tag::Tag(qreal _x, qreal _y, QString _text)
    : x(_x), y(_y), text(_text)
{
}

void Tag::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QBrush(QColor(255, 255, 102)));
    painter->drawRoundedRect(x, y, WIDTH, HEIGHT, 5, 5);
    painter->drawText(x + 5, y + 15, text);
}
