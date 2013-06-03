#ifndef TAG_H
#define TAG_H

#include "console.h"

#include <QGraphicsItem>
#include <QtGui>

class Tag : public QGraphicsItem
{
    friend class Console;
public:
    Tag(qreal _x, qreal _y, QString _text);

    static const int WIDTH  = 40;
    static const int HEIGHT = 20;

    void setText(QString _text)
    {
        text = _text;
        update();
    }

    QRectF boundingRect() const
    {
        return QRectF(x - 1, y - 1, WIDTH + 2, HEIGHT + 2);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

private:
    qreal x, y;
    QString text;
};

#endif // TAG_H
