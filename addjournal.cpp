#include "addjournal.h"
#include "ui_addjournal.h"
#include "QDebug"
#include "QSqlQuery"
AddJournal::AddJournal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddJournal)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Journal");
}

AddJournal::~AddJournal()
{
    delete ui;
}

void AddJournal::on_buttonBox_accepted()
{
   QString jName = ui->lineEdit->text();
   QString querystring = QString("INSERT INTO journal VALUES(NULL,'%1');").arg(jName);

   QSqlQuery qry;
   qry.exec(querystring);

}
