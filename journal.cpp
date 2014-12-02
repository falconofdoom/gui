#include "journal.h"
#include "ui_journal.h"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "addjournal.h"
#include "QDebug"
#include "QMessageBox"
Journal::Journal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Journal)
{
    ui->setupUi(this);
    setTableView();


}

Journal::~Journal()
{
    delete ui;
}

void Journal::on_toolButton_clicked()
{
    AddJournal *aj = new AddJournal;
    aj->exec();
   connect(aj,SIGNAL(destroyed()),aj,SLOT(deleteLater()));
    setTableView();

}

void Journal::on_toolButton_3_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();


    QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "Delete Journal", "Are you sure you want to delete this journal?",
                                   QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {

         QString data = ui->tableView->model()->data(ui->tableView->model()->
         index(index.row(),0)).toString();
         QSqlQuery delqry(QString("delete from journal where id = %1").arg(data));
         delqry.exec();
         setTableView();

     } else {
       qDebug() << "Yes was *not* clicked";
     }



}

void Journal::on_tableView_clicked(const QModelIndex &index)
{
    ui->tableView->selectRow(index.row());
}

void Journal::setTableView(){
    QSqlQueryModel *model = new QSqlQueryModel;

      model->setQuery("SELECT id,name FROM journal");
      model->setHeaderData(0,Qt::Horizontal,tr("ID"));
       model->setHeaderData(1,Qt::Horizontal,tr("Journal Name"));
      ui->tableView->setModel(model);
      ui->tableView->verticalHeader()->setVisible(false);


    ui->tableView->resizeColumnsToContents();
    QHeaderView* header = ui->tableView->horizontalHeader();

    header->setStretchLastSection(true);

    ui->tableView->setHorizontalHeader(header);
    ui->tableView->resizeRowsToContents();
}

void Journal::setIssueView(QString index){
    QSqlQueryModel *model = new QSqlQueryModel;

      model->setQuery(QString("SELECT volume FROM journal_issue where journal_id = %1").arg(index));
       model->setHeaderData(0,Qt::Horizontal,tr("Volume"));
      ui->tableView_2->setModel(model);
      ui->tableView_2->verticalHeader()->setVisible(false);


    ui->tableView_2->resizeColumnsToContents();
    QHeaderView* header = ui->tableView_2->horizontalHeader();

    header->setStretchLastSection(true);

    ui->tableView_2->setHorizontalHeader(header);
    ui->tableView_2->resizeRowsToContents();


}

void Journal::on_tableView_activated(const QModelIndex &index)
{
    QString data = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    qDebug()<<data.toInt();
    setIssueView(data);

}
