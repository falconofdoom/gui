#include "addauthor.h"
#include "ui_addauthor.h"

addAuthor::addAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addAuthor)
{
    ui->setupUi(this);
}

addAuthor::~addAuthor()
{
    delete ui;
}



void addAuthor::on_buttonBox_accepted()
{
    author=ui->lineEdit->text();
    affiliation=ui->lineEdit_2->text();
}
