#include "addauthor.h"
#include "ui_addauthor.h"

AddAuthor::AddAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addAuthor)
{
    ui->setupUi(this);
}

AddAuthor::~AddAuthor()
{
    delete ui;
}



void AddAuthor::on_buttonBox_accepted()
{
    author=ui->lineEdit->text();
    affiliation=ui->lineEdit_2->text();
}
