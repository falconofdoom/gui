#include "editarticle.h"
#include "ui_editarticle.h"

editarticle::editarticle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editarticle)
{
    ui->setupUi(this);
}

editarticle::~editarticle()
{
    delete ui;
}
