#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "console.h"

#include <QtGui/QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void actionAbout();

private:
    Console *console;
};

#endif // MAINWINDOW_H
