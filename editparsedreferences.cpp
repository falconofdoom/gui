#include "editparsedreferences.h"
#include "ui_editparsedreferences.h"

EditParsedReferences::EditParsedReferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditParsedReferences)
{
    ui->setupUi(this);
}

EditParsedReferences::~EditParsedReferences()
{
    delete ui;
}


void EditParsedReferences::changeError(int count)
{
    ui->label_2->setText(QString("%1").arg(count));
}


QHBoxLayout* EditParsedReferences::horLay()
{
    QHBoxLayout *ref = new QHBoxLayout;

    ref=ui->horizontalLayout;
    return ref;
}
