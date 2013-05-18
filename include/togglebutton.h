#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <QtGui>

class ToggleButton : public QGraphicsItem
{
public:
    explicit ToggleButton(qreal _x, qreal _y, int _id);

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
    static void initToggleButton();
    int id;

private:
    qreal x, y;
    static QPixmap *img_on, *img_off;
    bool state;
};

#endif // TOGGLEBUTTON_H
