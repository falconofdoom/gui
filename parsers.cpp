#include "parsers.h"
#include "ui_parsers.h"
#include "addparser.h"
#include "QMessageBox"
#include "QSqlQuery"
#include "QDebug"
parsers::parsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parsers)
{
    ui->setupUi(this);
    setTableView();

}

parsers::~parsers()
{
    delete ui;
}


void parsers::setTableView(){
    sqlmodel = new QSqlQueryModel;
    QString queryString = QString("SELECT * FROM parser");
    sqlmodel->setQuery(queryString);

    sqlmodel->setHeaderData(1,Qt::Horizontal,tr("Parser"));
    sqlmodel->setHeaderData(2,Qt::Horizontal,tr("Path"));

    ui->tableView->setModel(sqlmodel);

    ui->tableView->resizeColumnsToContents();
    QHeaderView* header2 = ui->tableView->horizontalHeader();

    header2->setStretchLastSection(true);

    ui->tableView->setHorizontalHeader(header2);
    ui->tableView->resizeRowsToContents();
    ui->tableView->setColumnHidden(0,true);
}

void parsers::on_addParser_clicked()
{
    addParser *ap = new addParser;

    int retcode = ap->exec();

    if(retcode==1) setTableView();

    connect(ap,SIGNAL(destroyed()),ap,SLOT(deleteLater()));
}

void parsers::on_delParser_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "Remove Parser",
                                "Are you sure you want to remove this parser" +
                                 QString(" from the program?")
                                ,QMessageBox::Yes|QMessageBox::No);


     if(reply == QMessageBox::Yes){
         QString data = ui->tableView->model()->data(ui->tableView->model()->
         index(index.row(),0)).toString();

         QSqlQuery delqry(QString("delete from parser where id = %1").arg(data));
         delqry.exec();

         setTableView();
     }



}

void parsers::on_tableView_clicked(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
}
