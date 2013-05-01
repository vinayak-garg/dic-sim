#ifndef IC_H
#define IC_H

#include "blockdata.h"
#include "console.h"

#include <QGraphicsItem>
#include <QString>

#include <vector>

class IC : public QGraphicsItem
{
    friend class Console;
public:
    explicit IC(QString _name, int _l, QPointF _pos, int _index,
                std::vector<BlockData> _blocks);

    explicit IC(QString _name, int _l, qreal _x, qreal _y, int _index,
                std::vector<BlockData> _blocks);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    std::vector<BlockData> blocks;
    int length()
    {
        return l;
    }

    int getindex()
    {
        return index;
    }

private:
    const QString name;
    qreal x, y;
    int l, index;
};

#endif // IC_H
