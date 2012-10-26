#ifndef BREADBOARD_H
#define BREADBOARD_H

#include <QWidget>

class Breadboard : public QWidget
{
    Q_OBJECT
public:
    explicit Breadboard(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void paintEvent(QPaintEvent *);
};

#endif // BREADBOARD_H
