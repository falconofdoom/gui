#include "viewjournal.h"
#include "ui_viewjournal.h"
#include "QDebug"
#include "QSqlQueryModel"
#include "QHeaderView"
#include "QBoxLayout"
#include "QSqlQuery"
#include "QSqlError"
#include "QMessageBox"
#include "QModelIndex"
#include "addissue.h"
#include "utility.h"
#include "editissue.h"

ViewJournal::ViewJournal(QString jID, QString jName, QString vID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewJournal)
{
    ui->setupUi(this);
    journID = jID;
    journName = jName;
    volID = vID;

    QString windowTitle = "Journal - " + journName + " Vol. " + volID;
    this->setWindowTitle(windowTitle);

    setIssueView();

}

void ViewJournal::setIssueView()
{
        QSqlQueryModel *model = new QSqlQueryModel;
        //Mquery stands for model query
        QString mQuery = "SELECT issue FROM journal_issue where journal_id = "
                          + journID + " and volume = " + volID
                          + " ORDER BY issue DESC";

        model->setQuery(mQuery);

        model->setHeaderData(0,Qt::Horizontal,tr("Issues"));

        ui->issueTable->setModel(model);
        ui->issueTable->verticalHeader()->setVisible(false);
        ui->issueTable->resizeColumnsToContents();
        QHeaderView* header = ui->issueTable->horizontalHeader();

        header->setStretchLastSection(true);

        ui->issueTable->setHorizontalHeader(header);
        ui->issueTable->resizeRowsToContents();

        ui->volumeLabel->setText("Volume: " + volID);
        ui->journalLabel->setText("Journal: " + journName);


        issue = ui->issueTable->model()->data(
                ui->issueTable->model()->index(0,0)
                ).toString();

        setLabels();

}

ViewJournal::~ViewJournal()
{
    delete ui;
}

void ViewJournal::on_issueTable_clicked(const QModelIndex &index)
{
     issue = ui->issueTable->model()->data(
             ui->issueTable->model()->index(index.row(),0)
             ).toString();
     //current issue will be equal to the content of clicked index
     setLabels();

}

void ViewJournal::setLabels(){
    QString selQuery = "SELECT * FROM journal_issue where journal_id = "
                       + journID + " and volume = " + volID
                       + " and issue = " + issue;

    QSqlQuery qry;
    qry.prepare(selQuery);


    if (!qry.exec() || !qry.first())
    {
       // SQL error (for example, if the table doesn't exist)

       QString errorText = qry.lastError().text();
       QMessageBox msgBox;
       msgBox.critical(0,"Error",errorText);
       msgBox.setFixedSize(500,200);
    }
    else
    {
        //set text of labels to appropriate data
        ui->issueLabel->setText("Issue: " + qry.value(2).toString());
        QString monthText = Utility::intToMonth(qry.value(3).toInt());
        ui->monthLabel->setText("Month: " + monthText);
        ui->yearLabel->setText("Year: " + qry.value(4).toString());
    }

}

void ViewJournal::on_addIssueButton_clicked()
{
    AddIssue * ai = new AddIssue;
    ai->setJournalDets(journID,journName,volID);
    int retcode = ai->exec();

    if(retcode==1){
        setIssueView();
        setLabels();

    }
    connect(ai,SIGNAL(destroyed()),ai,SLOT(deleteLater()));



}

void ViewJournal::on_deleteIssueButton_clicked()
{
    QModelIndex index = ui->issueTable->currentIndex();

    if(index.row() != -1){
         QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Delete Issue",
                    "Are you sure you want to delete this issue?",
                     QMessageBox::Yes|QMessageBox::No);

         if (reply == QMessageBox::Yes) {

             QString data = ui->issueTable->model()->data(ui->issueTable->model()->
             index(index.row(),0)).toString();

             QString delQStr = "delete from journal_issue where issue = "
                               + data + " and journal_id = " + journID +
                                " and volume = " + volID;

             QSqlQuery delQry(delQStr);
             delQry.exec();
             setIssueView();

         } else {
           qDebug() << "Yes was *not* clicked";
         }
    }
    else
    {
        QMessageBox warning;
        warning.setText("Please click first on an issue of you'd like to delete!");
        warning.setWindowTitle("No Issue Selected");
        warning.exec();
    }
}

void ViewJournal::on_editIssueButton_clicked()
{
    QModelIndex index = ui->issueTable->currentIndex();
    if(index.row() != -1){
        EditIssue *ei = new EditIssue;
        ei->setJournalDets(journID,journName,volID,issue);

        int retcode = ei->exec();
        if(retcode==1)
            setIssueView();
        connect(ei,SIGNAL(destroyed()),ei,SLOT(deleteLater()));
        connect(ei,SIGNAL(rejected()),ei,SLOT(deleteLater()));
    }
    else
    {
        QMessageBox warning;
        warning.setText("Please click first on an issue of you'd like to edit!");
        warning.setWindowTitle("No Issue Selected");
        warning.exec();
    }
 }
