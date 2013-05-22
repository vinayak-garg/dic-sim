#include "icdialog.h"

#include <QtGui>

ICDialog::ICDialog(QWidget *parent, QStringList *icName, QStringList *_icDesc) :
    QDialog(parent), icDesc(_icDesc)
{
    setWindowTitle("Available ICs");
    iclist = new QListWidget(this);
    iclist->addItems(*icName);
    connect(iclist, SIGNAL(itemSelectionChanged()),
            this, SLOT(actionICSelected()));

    QDialogButtonBox *buttonBox =
            new QDialogButtonBox(QDialogButtonBox::Ok
                                 | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    desc = new QLabel("Description of selected IC", this);
    desc->resize(200, 200);
    desc->setMargin(5);
    desc->setFixedWidth(200);
    desc->setAlignment(Qt::AlignTop);
    desc->setFrameStyle(QFrame::Panel);
    desc->setWordWrap(true);

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    hLayout->addWidget(iclist);
    hLayout->addWidget(desc);

    vLayout->addLayout(hLayout);
    vLayout->addWidget(buttonBox);

    setLayout(vLayout);
}

void ICDialog::actionICSelected()
{
    desc->setText(icDesc->at(iclist->currentRow()));
}
