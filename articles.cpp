#include "articles.h"
#include "ui_articles.h"
#include "QDebug"
#include "QHeaderView"
#include "QModelIndex"
#include "QSqlQuery"
#include "QSqlError"
Articles::Articles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Articles)
{
    ui->setupUi(this);
    ui->lineEdit->textChanged("*");
}

Articles::~Articles()
{
    delete ui;
}

void Articles::journalSetup(QString entry)
{
    sqlmodel = new QSqlQueryModel;
    QString wcard = entry;
    QString queryString = QString("SELECT * FROM JOURNAL WHERE NAME LIKE '\%%1\%'").arg(wcard);
    sqlmodel->setQuery(queryString);

    sqlmodel->setHeaderData(1,Qt::Horizontal,tr("Journal"));
    ui->tableView->setModel(sqlmodel);

    ui->tableView->resizeColumnsToContents();
    QHeaderView* header2 = ui->tableView->horizontalHeader();

    header2->setStretchLastSection(true);

    ui->tableView->setHorizontalHeader(header2);
    ui->tableView->resizeRowsToContents();
    ui->tableView->setColumnHidden(0,true);
}

void Articles::on_lineEdit_textChanged(const QString &arg1)
{
    journalSetup(ui->lineEdit->text());
}

void Articles::on_tableView_clicked(const QModelIndex &index)
{

    QString journID = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    QString data2 = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
    qDebug()<<data2;
     curJournName = data2;
     curJourn = journID;

     QSqlQueryModel *vol = new QSqlQueryModel;
     QString volquery = QString("SELECT volume FROM journal_volume where journal_id=%1").arg(journID);
     vol->setQuery(volquery);
     ui->comboBox->setModel(vol);

}

void Articles::on_comboBox_currentTextChanged(const QString &arg1)
{

    QString volData = ui->comboBox->currentText();
    curVol = volData;
    QSqlQueryModel *issue = new QSqlQueryModel;
    QString issuequery = QString("SELECT issue FROM journal_issue where journal_id=%1 and volume=%2").arg(curJourn).arg(volData);
    issue->setQuery(issuequery);
    ui->comboBox_2->setModel(issue);

}

void Articles::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    curIssue = ui->comboBox_2->currentText();

    QString queryString2 = QString("SELECT month,year FROM journal_issue WHERE journal_id = %1 and volume = %2 and issue = %3").arg(curJourn).arg(curVol).arg(curIssue);
    QSqlQuery qry;
    qry.prepare(queryString2);

    if (!qry.exec() || !qry.first())
    {
       qDebug() << qry.lastError().text();
       ui->label_3->setText("Month: ");
       ui->label_4->setText("Year: ");
    }
    else
    {
         int month = qry.value(0).toInt();
         int year = qry.value(1).toInt();

         ui->label_3->setText(QString("Month: %1").arg(month));
         ui->label_4->setText(QString("Year: %1").arg(year));

    }

    sqlmodel = new QSqlQueryModel;
    QString queryString = QString("SELECT * FROM article WHERE journal_id = %1 and volume_id = %2 and issue_id = %3").arg(curJourn).arg(curVol).arg(curIssue);
    sqlmodel->setQuery(queryString);

    sqlmodel->setHeaderData(1,Qt::Horizontal,tr("Articles"));
    ui->tableView_2->setModel(sqlmodel);

    ui->tableView_2->resizeColumnsToContents();
    QHeaderView* header3 = ui->tableView_2->horizontalHeader();

    header3->setStretchLastSection(true);

    ui->tableView_2->setHorizontalHeader(header3);
    ui->tableView_2->resizeRowsToContents();
    ui->tableView_2->setColumnHidden(0,true);
    ui->tableView_2->setColumnHidden(2,true);
    ui->tableView_2->setColumnHidden(3,true);
    ui->tableView_2->setColumnHidden(4,true);
    ui->tableView_2->setColumnHidden(5,true);
    ui->tableView_2->setColumnHidden(6,true);

}

void Articles::on_pushButton_clicked()
{

}
