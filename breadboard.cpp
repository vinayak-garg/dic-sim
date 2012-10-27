#include "breadboard.h"

#include <QtGui>

const int BB_WIDTH = 620;
const int BB_HEIGHT = 480;

Breadboard::Breadboard(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(BB_WIDTH, BB_HEIGHT);

    highlightColor.setRgb(0, 200, 0);
    selectedTColor.setRgb(255, 200, 0);
    selectedBColor.setRgb(240, 200, 0);
    terminalColor.setRgb(180, 180, 180);
    busColor.setRgb(185, 185, 185);
    borderColor.setRgb(80, 80, 80);
    backgroundColor.setRgb(254, 252, 250);

}

void Breadboard::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    const int x1 = kOuterBorder - 2,        //-2 for slight adjustment
        x2 = x1 + kCols*kBox - kBorder + 2;
    int x = kOuterBorder, y, i, j;

    //Terminal Contacts
    p.setBrush(QBrush(terminalColor));
    for(i = 0; i < kCols; x+=kBox, i++)
    {
        for(j = 0; j < 5; j++)
        {
            p.drawRect(x, ktR1 + j*kBox, kSquare, kSquare);
            p.drawRect(x, ktR2 + j*kBox, kSquare, kSquare);

            p.drawRect(x, ktR3 + j*kBox, kSquare, kSquare);
            p.drawRect(x, ktR4 + j*kBox, kSquare, kSquare);

            p.drawRect(x, ktR5 + j*kBox, kSquare, kSquare);
            p.drawRect(x, ktR6 + j*kBox, kSquare, kSquare);
        }
    }

    //Bus Contacts
    p.setBrush(QBrush(busColor));
    y = kOuterBorder + 10*kBox + kNotchGap + kBusBorder - 2*kBorder;
    for (i = 0, x = kOuterBorder; i < kBusCols; x+=kBusGap, i++)
    {
        for (j = 0; j < 5; x+=kBox, j++)
        {
            p.drawRect(x, kbR1, kSquare, kSquare);
            p.drawRect(x, kbR1 + kBox, kSquare, kSquare);
            p.drawRect(x, kbR2, kSquare, kSquare);
            p.drawRect(x, kbR2 + kBox, kSquare, kSquare);
        }
    }

    //Bus Lines
    p.setPen(QPen(QBrush(Qt::red), 2));
    p.drawLine(x1, y - 6, x2, y - 6);
    p.drawLine(x1, y + 2*kBusBorder + 12*kBox + kNotchGap - 3*kBorder - 6, x2, y + 2*kBusBorder + 12*kBox + kNotchGap - 3*kBorder - 6);
    p.setPen(QPen(QBrush(Qt::blue), 2));
    p.drawLine(x1, y + 2*kBox - kBorder + 6, x2, y + 2*kBox - kBorder + 6);
    p.drawLine(x1, y + 2*kBusBorder + 14*kBox + kNotchGap - 4*kBorder + 6, x2, y + 2*kBusBorder + 14*kBox + kNotchGap - 4*kBorder + 6);

    //Notch
    p.setPen(QPen(QBrush(Qt::gray), 5));
    y = kOuterBorder + 5*kBox - kBorder + (kNotchGap>>1);
    p.drawLine(x1, y, x2, y);
    y += 12*kBox - 3*kBorder + 2*kBusBorder + kNotchGap;
    p.drawLine(x1, y, x2, y);
    y += 12*kBox - 3*kBorder + 2*kBusBorder + kNotchGap;
    p.drawLine(x1, y, x2, y);
}

void Breadboard::mousePressEvent(QMouseEvent *)
{
    //QMessageBox::information(this, "now now", "inside breadboard!");

}

void Breadboard::mouseMoveEvent(QMouseEvent *e)
{
    QPixmap pixmap = QPixmap::grabWindow(winId());
    QRgb color = pixmap.toImage().pixel(e->x(), e->y());
    if (QColor(color) == terminalColor)
        QMessageBox::information(this, "Ter", "minal");
}
