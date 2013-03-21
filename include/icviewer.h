#ifndef ICVIEWER_H
#define ICVIEWER_H

#include <QWidget>

class ICViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ICViewer(QWidget *parent, QString _num, QString _label);
    
signals:
    
public slots:

protected:
    void paintEvent(QPaintEvent *);
private:
    QString num;
    QStringList labels;
    int len;
};

#endif // ICVIEWER_H
