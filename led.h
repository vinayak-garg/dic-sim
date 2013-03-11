#ifndef LED_H
#define LED_H

#include <QtGui>

const int8_t STATE = 1;
const int8_t POWER = 2;

class LED : public QGraphicsItem
{
public:
    explicit LED(QPointF p1, QPointF p2);
    //explicit LED(qreal _x1, qreal _y1, qreal _x2, qreal _y2);
    void set(qreal _x1, qreal _y1, qreal _x2, qreal _y2);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    bool isOn()
    {
        return (state & STATE) & POWER;
    }
    QLineF line() const
    {
        return QLineF(x1, y1, x2, y2);
    }

    static void initLed();
    static bool validDistance(QPointF p1, QPointF p2);

public slots:
    void switchOn(int8_t SorP = STATE)
    {
        state |= SorP;
    }
    void switchOff(int8_t SorP = STATE)
    {
        state &= ~SorP;
    }

private:
    qreal x1, y1, x2, y2, x, y, w, h;
    int8_t state;
    static QPixmap *led_on, *led_off;
};

#endif // LED_H
