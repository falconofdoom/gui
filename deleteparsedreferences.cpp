#include "deleteparsedreferences.h"
#include "ui_deleteparsedreferences.h"
#include "QModelIndex"
#include "QDebug"
#include "QAbstractItemModel"
#include "QMessageBox"
#include "QSqlQuery"
DeleteParsedReferences::DeleteParsedReferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteParsedReferences)
{
    ui->setupUi(this);
   model = new QSqlQueryModel;

      model->setQuery("SELECT id,name FROM reference");
      model->setHeaderData(0,Qt::Horizontal,tr("ID"));
       model->setHeaderData(1,Qt::Horizontal,tr("Identifier"));
      ui->tableView->setModel(model);


    ui->tableView->resizeColumnsToContents();
    QHeaderView* header = ui->tableView->horizontalHeader();

    header->setStretchLastSection(true);

    ui->tableView->setHorizontalHeader(header);
    ui->tableView->resizeRowsToContents();
    ui->tableView->setColumnHidden(0,true);
}

DeleteParsedReferences::~DeleteParsedReferences()
{
    delete ui;
}

void DeleteParsedReferences::on_tableView_clicked(const QModelIndex &index)
{
    delIndex = index;
}


void DeleteParsedReferences::on_pushButton_clicked()
{
    QString data = ui->tableView->model()->data(ui->tableView->model()->index(delIndex.row(),0)).toString();

    QSqlQuery qry;
    QString delRefQuery = QString("delete from reference where id=%1").arg(data);
    QString delCitQuery = QString("delete from citation where reference_id=%1").arg(data);
   qDebug()<<delRefQuery;
      qDebug()<<delCitQuery;
    QSqlQuery query1;
    QSqlQuery query2;


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Deleting Reference", "Are you sure you want to delete this and its associated entries?", QMessageBox::Yes|QMessageBox::No);

    QMessageBox alert;

    if (reply == QMessageBox::Yes) {
      qDebug() << "Yes was clicked";
      query1.exec(delRefQuery);
      query2.exec(delCitQuery);
      alert.setText("Successfully Deleted!");
      alert.setWindowTitle("Success!");
      alert.show();
    } else {

    }




    model->setQuery("SELECT id,name FROM reference");
   // ui->tableView->model()->layoutChanged();
}

void DeleteParsedReferences::on_DeleteParsedReferences_destroyed()
{
    delete model;
}
