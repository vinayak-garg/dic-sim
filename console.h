#ifndef CONSOLE_H
#define CONSOLE_H

#include "breadboard.h"
//#include <QWidget>
#include <QtGui>

class Console : public QWidget
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void paintEvent(QPaintEvent *);
    //void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    Breadboard *breadboard;
};

#endif // CONSOLE_H
