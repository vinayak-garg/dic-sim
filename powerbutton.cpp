#include "powerbutton.h"

#include <QtGui>

QPixmap* PowerButton::img_on;
QPixmap* PowerButton::img_off;

PowerButton::PowerButton(qreal _x, qreal _y) : x(_x), y(_y)
{
    state = false;
}

QRectF PowerButton::boundingRect() const
{
    return QRectF(x, y, img_on->width(), img_on->height());
}

void PowerButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(x, y, isOn() ? *img_on : *img_off);
}

void PowerButton::init()
{
    img_on = new QPixmap(":/button/main_on");
    img_off = new QPixmap(":/button/main_off");
}

/*
void PowerButton::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
}
*/
