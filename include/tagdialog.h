#ifndef TAGDIALOG_H
#define TAGDIALOG_H

#include <QtGui>

class TagDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TagDialog(QWidget *parent, int _n);
    bool getInputOrOutput()
    {
        return io;
    }
    int getNumber()
    {
        return number;
    }
    QString getText()
    {
        return text;
    }

signals:

public slots:
    void actionRadioToggled();
    void actionNumberChanged();
    void actionTextChanged();

private:
    int n;
    bool io;
    int number;
    QString text;

    QRadioButton *inRB, *outRB;
    QSpinBox *spinB;
    QLineEdit *textLE;
};

#endif // TAGDIALOG_H
