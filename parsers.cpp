#include "parsers.h"
#include "ui_parsers.h"
#include "addparser.h"
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

void parsers::on_pushButton_clicked()
{
    addParser *ap = new addParser;

    int retcode = ap->exec();

    if(retcode==1) setTableView();

    connect(ap,SIGNAL(destroyed()),ap,SLOT(deleteLater()));

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
