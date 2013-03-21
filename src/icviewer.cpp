#include "icviewer.h"

#include <QtGui>

const int kXpos = 10;
const int kYpos = 30;

const int kIcWidth = 50;
const int kIcPinWidth = 15;
const int kIcPinSeparation = 10;
const int kIcPinHeight = 10;


ICViewer::ICViewer(QWidget *parent, QString _num, QString _label) :
    QWidget(parent, Qt::Tool), num(_num)
{
    this->resize(250, 120);
    setWindowTitle(_num);
    labels = _label.split(' ', QString::SkipEmptyParts);
    len = labels.size()/2;
}

void ICViewer::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QBrush b(Qt::black);
    p.fillRect(kXpos + kIcPinSeparation/2, kYpos,
               (kIcPinSeparation + kIcPinWidth)*len, kIcWidth, Qt::black);
    b.setColor(Qt::yellow);
    for (int i = 0; i < len; ++i)
    {
        p.fillRect(kXpos + (i+1)*kIcPinSeparation + i*kIcPinWidth, kYpos - kIcPinHeight,
            kIcPinWidth, kIcPinHeight, b);
        p.fillRect(kXpos + (i+1)*kIcPinSeparation + i*kIcPinWidth, kYpos + kIcWidth,
            kIcPinWidth, kIcPinHeight, b);
    }

    p.setPen(Qt::black);

    QFontMetrics fm = p.fontMetrics();
    //Lower Row of Pins
    int i, j;
    for (i = 0; i < (labels.size())/2; ++i)
        p.drawText(kXpos + (i+1)*kIcPinSeparation + i*kIcPinWidth + kIcPinWidth/2 - fm.width(labels[i])/2,
        kYpos + kIcWidth + 25, labels[i]);

    //Upper Row of Pins
    for (j = i; i < labels.size(); ++i, --j)
        p.drawText(kXpos + j*(kIcPinSeparation + kIcPinWidth) - kIcPinWidth,
        kYpos - 15, labels[i]);

    //IC name
    p.setFont(QFont("Arial", 20, QFont::Bold));
    p.setPen(Qt::white);
    fm = p.fontMetrics();
    p.drawText(kXpos + (kIcPinSeparation + kIcPinWidth)*len/2 - fm.width(num)/2,
               kYpos + kIcWidth/2 + fm.height()/2, num);
}
