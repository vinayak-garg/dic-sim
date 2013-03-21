#ifndef IC_H
#define IC_H

#include <QGraphicsItem>
#include <QString>

class IC : public QGraphicsItem
{
public:
    explicit IC(QString _name, int _l, QPointF _pos);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
private:
    QString name;
    qreal x, y;
    int l;
};

#endif // IC_H
