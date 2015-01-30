#include "editissue.h"
#include "ui_editissue.h"
#include "QDebug"
#include "QMessageBox"
#include "QSqlError"
#include "QSqlQuery"

EditIssue::EditIssue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editIssue)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit Issue");

}

EditIssue::~EditIssue()
{
    delete ui;
}
void EditIssue::setJournalDets(QString jI, QString jN, QString vol, QString iID)
{
    jName=jN;
    jIndex=jI;
    jVol = vol;
    qDebug()<<jName<<" "<<jIndex<<" "<<jVol;
    ui->journalNameLabel->setText("Journal: " + jName);
    ui->volumeLabel->setText("Volume: " + jVol);

    ui->spinBox->setValue(iID.toInt());

    QString selQry = "select * from journal_issue where journal_id = " +
                     jIndex + " and volume = " + jVol +
                     " and issue = " + iID;

    QSqlQuery qry;

    qry.exec(selQry);

    qry.next();
    issueID=qry.value(0).toString();
    issueNum = iID;
    ui->spinBox_2->setValue(qry.value(4).toInt());
    ui->comboBox->setCurrentIndex(qry.value(3).toInt()-1);

}

void EditIssue::on_buttonBox_accepted()
{
    QString issue = ui->spinBox->text();
    QMap <QString,QString> qm;

    // loop through 1-12 and convert month into text form
     for(int i=1;i<=12;i++)
     {
       qm[ui->comboBox->itemText(i-1)]=QString("%1").arg(i);
     }
     QString month = qm[ui->comboBox->currentText()];
     QString year = ui->spinBox_2->text();

     // update query
     QString upd =
        "UPDATE journal_issue SET issue = " + issue +
        ", year = " + year + ", month = " + month +
        " WHERE id = " + issueID;



    QSqlQuery query1;
    QString prep =
    QString("Select count(*) from journal_issue where journal_id=%1 and volume=%2 and issue=%3")
                .arg(jIndex).arg(jVol).arg(issue);

    query1.prepare(prep);
    // Try to execute the query and position the result on the first and unique record
    if (!query1.exec() || !query1.first())
    {
       // SQL error (for example, if the table doesn't exist)
       qDebug() << query1.lastError().text();
    }
    // value(0) of first record will contain the "count(*)" value
    else if (query1.value(0) == 0)
    {
        QSqlQuery updqry;
        updqry.exec(upd);
    }
    else
    {
         QMessageBox msgBox;
         msgBox.critical(0,"Error","Duplicating issues are not allowed");
         msgBox.setFixedSize(500,200);
    }
}
