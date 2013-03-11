#ifndef ICDIALOG_H
#define ICDIALOG_H

#include <QtGui>

class ICDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ICDialog(QWidget *parent, QStringList *icName,
                      QStringList *_icDesc);
    int getIndex()
    {
        return iclist->currentRow();
    }

signals:
    
public slots:
    void actionICSelected();
private:
    QListWidget *iclist;
    QLabel *desc;
    QStringList *icDesc;
};

#endif // ICDIALOG_H
