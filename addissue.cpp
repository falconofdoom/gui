#include "addissue.h"
#include "ui_addissue.h"
#include "QDebug"
#include "QMessageBox"
#include "QSqlError"
#include "QSqlQuery"
AddIssue::AddIssue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addIssue)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Issue");
}

AddIssue::~AddIssue()
{
    delete ui;
}
void AddIssue::setJournalDets(QString jI,QString jN,QString vol)
{
    jName=jN;
    jIndex=jI;
    jVol = vol;
    qDebug()<<jName<<" "<<jIndex<<" "<<jVol;
    ui->journalNameLabel->setText("Journal: " + jName);
    ui->volumeLabel->setText("Volume: " + jVol);
}

void AddIssue::on_buttonBox_accepted()
{
    QString issue = ui->spinBox->text();
    QMap <QString,QString> qm;

     for(int i=1;i<=12;i++)
     {
       qm[ui->comboBox->itemText(i-1)]=QString("%1").arg(i);
     }
     QString month = qm[ui->comboBox->currentText()];
     QString year = ui->spinBox_2->text();

     QString ins =
         QString("insert into journal_issue values(NULL,%1,%2,%3,%4,%5)")
             .arg(jVol).arg(issue).arg(month).arg(year).arg(jIndex);

    qDebug()<<ins;



    QSqlQuery query1;

    query1.prepare(QString("Select count(*) from journal_issue where journal_id=%1 and volume=%2 and issue=%3").arg(jIndex).arg(jVol).arg(issue));
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
         msgBox.critical(0,"Error","The issue for the specified volume already exists in the database!");
         msgBox.setFixedSize(500,200);
    }



}
