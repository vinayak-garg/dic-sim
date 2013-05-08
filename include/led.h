#ifndef LED_H
#define LED_H

#include <QtGui>

const int STATE = 1;
const int POWER = 2;

class LED : public QGraphicsItem
{
public:
    explicit LED(QPointF p1, QPointF p2);
    void set(qreal _x1, qreal _y1, qreal _x2, qreal _y2);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    bool isOn()
    {
        return (state & STATE) && (state & POWER);
    }
    QLineF line() const
    {
        return QLineF(x1, y1, x2, y2);
    }

    static void initLed();
    static bool validDistance(QPointF p1, QPointF p2);

public slots:
    void switchOn(int SorP = STATE)
    {
        state |= SorP;
        update();
    }
    void switchOff(int SorP = STATE)
    {
        state &= ~SorP;
        update();
    }

private:
    qreal x1, y1, x2, y2, x, y, w, h;
    int state;
    static QPixmap *led_on, *led_off;
};

#endif // LED_H
