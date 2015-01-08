#include "viewarticle.h"
#include "ui_viewarticle.h"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include "QMessageBox"
#include "QDebug"

#include "utility.h"
ViewArticle::ViewArticle(QString artID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewArticle)
{
    ui->setupUi(this);

    QString articleQuery = "SELECT * FROM article where id = " + artID;
    QString authorsQuery = "SELECT * from author where article_id = " + artID;

    QSqlQuery qry;
    qry.prepare(articleQuery);

    //fill in tableview items for authors
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(authorsQuery);
    model->setHeaderData(1,Qt::Horizontal,tr("Author"));
    model->setHeaderData(2,Qt::Horizontal,tr("Affiliation"));
    ui->tableView->setModel(model);
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->resizeColumnsToContents();
    QHeaderView* header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(3,true);
    ui->tableView->setHorizontalHeader(header);
    ui->tableView->resizeColumnsToContents();





    if (!qry.exec() || !qry.first())
    {
       // SQL error (for example, if the table doesn't exist)
        QMessageBox msgBox;
        msgBox.critical(0,"Error","No article selected, please select and try again");
        msgBox.setFixedSize(500,200);
    }
    else
    {

        QString journalID = qry.value(4).toString();
        QString article = qry.value(1).toString();
        QString volume = qry.value(5).toString();
        QString issue = qry.value(6).toString();
        QString parser = qry.value(3).toString();
        QString yM= "SELECT month,year from journal_issue where journal_id = " +
                    journalID + " and volume = " + volume + " and issue = "
                    + issue;
        QSqlQuery yMquery,jQuery;
        yMquery.exec(yM);
        yMquery.next();

        jQuery.exec("SELECT name from journal where id = " + journalID);
        jQuery.next();
        QString journal = jQuery.value(0).toString();
        QString month = Utility::intToMonth(yMquery.value(0).toInt());
        QString year = yMquery.value(1).toString();

        ui->articleLabel->setText("Article Title: " + article);
        this->setWindowTitle("Article - " + article);
        ui->journalLabel->setText("Journal: " + journal);
        ui->volumeLabel->setText("Volume: " + volume);
        ui->issueLabel->setText("Issue: " + issue);
        ui->monthLabel->setText("Month: " + month);
        ui->yearLabel->setText("Year: " + year);
        ui->parserLabel->setText("Parser used: " + parser);
    }


}

ViewArticle::~ViewArticle()
{
    delete ui;
}
