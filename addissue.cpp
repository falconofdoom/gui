#include "addissue.h"
#include "ui_addissue.h"
#include "QDebug"
#include "QSqlQuery"
addIssue::addIssue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addIssue)
{
    ui->setupUi(this);
}

addIssue::~addIssue()
{
    delete ui;
}
void addIssue::setJournalDets(QString jI,QString jN,QString vol)
{
    jName=jN;
    jIndex=jI;
    jVol = vol;
    qDebug()<<jName<<" "<<jIndex<<" "<<jVol;
    ui->label_4->setText(jName);
}

void addIssue::on_buttonBox_accepted()
{
    QString issue = ui->spinBox->text();
    QMap <QString,QString> qm;

     for(int i=1;i<=12;i++)
     {
       qm[ui->comboBox->itemText(i-1)]=QString("%1").arg(i);
     }
     QString month = qm[ui->comboBox->currentText()];
     QString year = ui->spinBox_2->text();

QString ins = QString("insert into journal_issue values(NULL,%1,%2,%3,%4,%5)")
        .arg(jVol).arg(issue).arg(month).arg(year).arg(jIndex);

    qDebug()<<ins;
    QSqlQuery insqry;
    insqry.exec(ins);
}
