#include "tagdialog.h"

#include <QtGui>

TagDialog::TagDialog(QWidget *parent, int _n) :
    QDialog(parent), n(_n)
{
    setWindowTitle("Set Tag");

    QDialogButtonBox *buttonBox =
            new QDialogButtonBox(QDialogButtonBox::Ok
                                 | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    QGridLayout *gLayout = new QGridLayout;

    inRB = new QRadioButton("Input");
    outRB = new QRadioButton("Output");
    hLayout->addWidget(inRB);
    hLayout->addWidget(outRB);
    inRB->setChecked(true);
    connect(inRB, SIGNAL(toggled(bool)), this, SLOT(actionRadioToggled()));

    QLabel *numberL = new QLabel("Number");
    spinB = new QSpinBox();
    spinB->setRange(1, n);
    connect(spinB, SIGNAL(valueChanged(int)), this, SLOT(actionNumberChanged()));

    QLabel *textL = new QLabel("Text");
    textLE = new QLineEdit;
    connect(textLE, SIGNAL(textChanged(QString)), this, SLOT(actionTextChanged()));

    gLayout->addLayout(hLayout, 1, 1, 1, 2);
    gLayout->addWidget(numberL, 2, 1);
    gLayout->addWidget(spinB, 2, 2);
    gLayout->addWidget(textL, 3, 1);
    gLayout->addWidget(textLE, 3, 2);

    vLayout->addLayout(gLayout);
    vLayout->addWidget(buttonBox);

    setLayout(vLayout);

    io = true;
    number = 1;
}

void TagDialog::actionRadioToggled()
{
    io = inRB->isChecked();
}

void TagDialog::actionNumberChanged()
{
    number = spinB->value();
}

void TagDialog::actionTextChanged()
{
    text = textLE->text();
    text.truncate(3);
    textLE->setText(text);
}
