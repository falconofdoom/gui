#include "editarticle.h"
#include "ui_editarticle.h"
#include "QSqlQuery"
#include "QMessageBox"
#include "QDebug"
#include "addauthor.h"
#include "utility.h"
#include "QStandardItem"

typedef QList< QStandardItem* > StandardItemList;


EditArticle::EditArticle(QString artID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editarticle)
{
    ui->setupUi(this);

    QString articleQuery = "SELECT * FROM article where id = " + artID;
    QString authorsQuery = "SELECT * from author where article_id = " + artID;

    QSqlQuery qry;
    qry.prepare(articleQuery);

    //fill in tableview items for authors

    model = new QStandardItemModel(0,2);
    ui->tableView->setModel(model);

    QSqlQueryModel *sqlmodel = new QSqlQueryModel;
    sqlmodel->setQuery(authorsQuery);
    model->setHeaderData(0,Qt::Horizontal,tr("Author"));
    model->setHeaderData(1,Qt::Horizontal,tr("Affiliation"));
    for(int i=0; i < sqlmodel->rowCount();i++)
    {
        QString authstr = sqlmodel->data(sqlmodel->index(i,1)).toString();
        QString affilstr = sqlmodel->data(sqlmodel->index(i,2)).toString();
        QStandardItem *auth = new QStandardItem(authstr);
        QStandardItem *affil = new QStandardItem(affilstr);
        model->appendRow( StandardItemList() << auth << affil );
    }

    ui->tableView->setModel(model);
    QHeaderView* header = ui->tableView->horizontalHeader();

    header->setSectionResizeMode(QHeaderView::Stretch);

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
        qDebug()<<yM;
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

EditArticle::~EditArticle()
{
    delete ui;
}

void EditArticle::on_addAuthor_clicked()
{
    addAuthor *aA = new addAuthor;
     int retcode = aA->exec();

     if(retcode==1){

           QStandardItem *auth = new QStandardItem(QString(aA->author));
           QStandardItem *affil = new QStandardItem(QString(aA->affiliation));

         if(aA->author.trimmed() != "" && aA->affiliation.trimmed() != "")
               model->appendRow( StandardItemList() << auth << affil );
         else
         {
             QMessageBox warning;
             warning.setText("One of the fields were left blank! Please try again! This transaction will not be saved!");
             warning.setWindowTitle("No Journal Selected");
             warning.exec();
         }
    }
}

void EditArticle::on_removeAuthor_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    if(index.row() != -1)
        model->removeRow(index.row());
    else
    {
        QMessageBox warning;
        warning.setText("No author selected to be removed! Please select an author then try again!");
        warning.setWindowTitle("No Author Selected");
        warning.exec();
    }
}
