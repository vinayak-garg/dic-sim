#include "console.h"
#include "cell.h"
#include "wire.h"

#include <QPushButton>
#include <QGridLayout>

const int CONSOLE_WIDTH = 900;
const int CONSOLE_HEIGHT = 640;

Console::Console(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(CONSOLE_WIDTH, CONSOLE_HEIGHT);

    //setStyleSheet("background: #cccc00;");

    QLabel *button2 = new QLabel(this);

    QPixmap pixmap(":/button/images/components/mainswitch_off.png");
    button2->setPixmap(pixmap);
    //button2->setIconSize(pixmap.rect().size());

    breadboard = new Breadboard(this);
    breadboard->setObjectName(QObject::tr("breadboard"));
    QPushButton *button4 = new QPushButton("Four");
    QPushButton *button5 = new QPushButton("Five");

    QGridLayout *layout = new QGridLayout(this);
    //layout->addWidget(button1, 0, 0);
    layout->addWidget(button2, 0, 1);

    QGraphicsView *view = new QGraphicsView(breadboard);
    view->setFixedSize(Breadboard::BB_WIDTH, Breadboard::BB_HEIGHT);
    layout->addWidget(view, 1, 0, 1, 2);
    //view.show();
    //layout->addWidget(breadboard, 1, 0, 1, 2);
    layout->addWidget(button4, 2, 0);
    layout->addWidget(button5, 2, 1);

    setLayout(layout);
    //show();
}

void Console::setWireColor(QColor color)
{
    breadboard->setWireColor(color);
}

void Console::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Console::mousePressEvent(QMouseEvent *)
{
    //QMessageBox::information(this, "Ouch!", "You pressed it.");
}
