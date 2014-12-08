#include "parsewizard.h"
#include "ui_parsewizard.h"
#include "QLabel"
#include "QStandardItem"
#include "QHeaderView"
#include "addauthor.h"
#include "QList"
#include "QDebug"
#include"QMessageBox"
typedef QList< QStandardItem* > StandardItemList;

parseWizard::parseWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::parseWizard)
{
    ui->setupUi(this);

    ui->tableView->alternatingRowColors();
    model = new QStandardItemModel(0,2);
    ui->tableView->setModel(model);

    model->setHeaderData(0,Qt::Horizontal,tr("Author"));
     model->setHeaderData(1,Qt::Horizontal,tr("Affiliation"));
    ui->tableView->setModel(model);


  ui->tableView->resizeColumnsToContents();
  QHeaderView* header = ui->tableView->horizontalHeader();

  for(int i=0;i<header->count();i++)
     header->setSectionResizeMode(i,QHeaderView::Stretch);

  ui->tableView->setHorizontalHeader(header);
  ui->tableView->resizeRowsToContents();
}

parseWizard::~parseWizard()
{
    delete ui;
}

void parseWizard::on_label_2_linkActivated(const QString &link)
{

}

void parseWizard::authorAdded()
{
    qDebug()<<"TEST AUTHOR ADDED";
}

void parseWizard::on_pushButton_clicked()
{
    addAuthor *aA = new addAuthor;
     int retcode = aA->exec();

     if(retcode==1){
       QStandardItem *auth = new QStandardItem(QString(aA->author));
       QStandardItem *affil = new QStandardItem(QString(aA->affiliation));
       model->appendRow( StandardItemList() << auth << affil );

     }\


    connect(aA,SIGNAL(destroyed()),aA,SLOT(deleteLater()));
}

void parseWizard::on_lineEdit_2_textChanged(const QString &arg1)
{
    sqlmodel = new QSqlQueryModel;
    QString wcard = ui->lineEdit_2->text();
    QString queryString = QString("SELECT * FROM JOURNAL WHERE NAME LIKE '\%%1\%'").arg(wcard);
    sqlmodel->setQuery(queryString);

    sqlmodel->setHeaderData(1,Qt::Horizontal,tr("Journal"));
    ui->tableView_2->setModel(sqlmodel);

    ui->tableView_2->resizeColumnsToContents();
    QHeaderView* header = ui->tableView_2->horizontalHeader();

    header->setStretchLastSection(true);

    ui->tableView_2->setHorizontalHeader(header);
    ui->tableView_2->resizeRowsToContents();
    ui->tableView_2->setColumnHidden(0,true);


}
