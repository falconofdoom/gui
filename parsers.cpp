#include "parsers.h"
#include "ui_parsers.h"

parsers::parsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parsers)
{
    ui->setupUi(this);
}

parsers::~parsers()
{
    delete ui;
}
