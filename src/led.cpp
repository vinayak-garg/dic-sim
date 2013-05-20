#include "led.h"
#include "utility.h"
#include <QtGui>

QPixmap* LED::led_on;
QPixmap* LED::led_off;

LED::LED(QPointF p1, QPointF p2, int _col)
{
    set(p1.x(), p1.y(), p2.x(), p2.y());
    switchOff(STATE);
    col = _col;
}

void LED::set(qreal _x1, qreal _y1, qreal _x2, qreal _y2)
{
    x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2;
    x = math::min(x1, x2);
    y = math::min(y1, y2);
    w = math::abs(x1 - x2);
    h = math::abs(y1 - y2);
}

QRectF LED::boundingRect() const
{
    qreal pw = led_on->width() + 2;
    return QRectF(x - pw/2, y - pw/2, w + pw, h + pw);
}

void LED::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(x1, y1, x2, y2);
    painter->drawPixmap(x + w/2 - led_on->width()/2,
                        y + h/2 - led_on->height()/2,
                        isOn() ? *led_on : *led_off);
}

void LED::initLed()
{
    led_on = new QPixmap(":/components/led_on");
    led_off = new QPixmap(":/components/led_off");
}

bool LED::validDistance(QPointF p1, QPointF p2)
{
    QPointF d = p1 - p2;
    return (d.x()*d.x() + d.y()*d.y() <= 6400.0);
}
