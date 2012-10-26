#include "breadboard.h"

#include <QtGui>

const int BB_WIDTH = 600;
const int BB_HEIGHT = 400;

Breadboard::Breadboard(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(BB_WIDTH, BB_HEIGHT);
}

void Breadboard::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    p.drawLine(100, 200, 300, 400);
}
