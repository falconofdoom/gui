#include "editrefindb.h"
#include "ui_editrefindb.h"

EditRefInDB::EditRefInDB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditRefInDB)
{
    ui->setupUi(this);
}

EditRefInDB::~EditRefInDB()
{
    delete ui;
}

