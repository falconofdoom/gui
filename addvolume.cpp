#include "addvolume.h"
#include "ui_addvolume.h"
#include "QDebug"
#include "QSqlQuery"
#include "QSqlError"
#include "QMessageBox"
AddVolume::AddVolume(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addVolume)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Volume");
}

void AddVolume::setJournalDets(QString jI,QString jN)
{
    jName=jN;
    jIndex=jI;
    ui->label_2->setText(jName);

}


AddVolume::~AddVolume()
{
    delete ui;
}

void AddVolume::on_buttonBox_accepted()
{
    QString issue = ui->spinBox->text();
   QString ins = QString("insert into journal_volume values(NULL,%1,%2)").arg(issue).arg(jIndex);

   QSqlQuery query1;

   query1.prepare(QString("Select count(*) from journal_volume where journal_id=%1 and volume=%2").arg(jIndex).arg(issue));
   // Try to execute the query and position the result on the first and unique record
   if (!query1.exec() || !query1.first())
   {
      // SQL error (for example, if the table doesn't exist)
      qDebug() << query1.lastError().text();
   }
   // value(0) of first record will contain the "count(*)" value
   else if (query1.value(0) == 0)
   {
       QSqlQuery insqry;
       insqry.exec(ins);
   }
   else
   {
        QMessageBox msgBox;
        msgBox.critical(0,"Error","Volume already exists in the database!");
        msgBox.setFixedSize(500,200);
   }



}
