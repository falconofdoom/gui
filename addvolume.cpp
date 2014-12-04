#include "addvolume.h"
#include "ui_addvolume.h"
#include "QDebug"
#include "QSqlQuery"
addVolume::addVolume(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addVolume)
{
    ui->setupUi(this);
}

void addVolume::setJournalDets(QString jI,QString jN)
{
    jName=jN;
    jIndex=jI;
    ui->label_2->setText(jName);

}


addVolume::~addVolume()
{
    delete ui;
}

void addVolume::on_buttonBox_accepted()
{
    QString issue = ui->spinBox->text();
   QString ins = QString("insert into journal_volume values(NULL,%1,%2)").arg(issue).arg(jIndex);


    QSqlQuery insqry;
    insqry.exec(ins);
}
