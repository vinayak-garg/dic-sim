#ifndef POWERBUTTON_H
#define POWERBUTTON_H

#include <QtGui>

class PowerButton : public QGraphicsItem
{
public:
    explicit PowerButton(qreal _x, qreal _y);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void set(bool _state)
    {
        if (state != _state)
        {
            state = _state;
            update();
        }
    }
    bool isOn()
    {
        return state;
    }

    static void init();

protected:
    //void mousePressEvent(QMouseEvent *ev);
public slots:
private:
    qreal x, y;
    static QPixmap *img_on, *img_off;
    bool state;
};

#endif // POWERBUTTON_H
