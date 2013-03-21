#include "togglebutton.h"

#include <QtGui>

QPixmap* ToggleButton::img_off;
QPixmap* ToggleButton::img_on;

ToggleButton::ToggleButton(qreal _x, qreal _y) :x(_x), y(_y)
{
    state = false;
}

void ToggleButton::initToggleButton()
{
    img_off = new QPixmap(":/button/toggle_off");
    img_on = new QPixmap(":/button/toggle_on");
}

QRectF ToggleButton::boundingRect() const
{
    return QRectF(x, y, img_on->width(), img_on->height());
}

void ToggleButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(x, y, isOn() ? *img_on : *img_off);
}

/*
void ToggleButton::mousePressEvent(QMouseEvent *ev)
{
    state = !state;
    if (state)
        setPixmap(*button_on);
    else
        setPixmap(*button_off);
    emit clicked();
}
*/
