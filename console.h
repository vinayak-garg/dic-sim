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

private:
    Breadboard *breadboard;
};

#endif // CONSOLE_H
