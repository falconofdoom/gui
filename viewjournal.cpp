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
                          + journID + " and volume = " + volID;

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
        ui->monthLabel->setText("Month: " + qry.value(3).toString());
        ui->yearLabel->setText("Year: " + qry.value(4).toString());
    }

}
