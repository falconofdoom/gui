#include "journal.h"
#include "ui_journal.h"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "addjournal.h"
#include "QDebug"
#include "QMessageBox"
#include "addvolume.h"
/* Current Journal Selected */
QString curJourn;
QString curIssue;
QString curJournName;
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

void Journal::setVolumeView(QString index){
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

void Journal::setIssueView(QString index){
    QSqlQueryModel *model = new QSqlQueryModel;

      model->setQuery(QString("SELECT issue,month,year FROM journal_issue where journal_id = %1 and volume = %2").arg(curJourn).arg(index));
       //model->setHeaderData(0,Qt::Horizontal,tr("Volume"));
      ui->tableView_3->setModel(model);
      ui->tableView_3->verticalHeader()->setVisible(false);


    ui->tableView_3->resizeColumnsToContents();
    QHeaderView* header = ui->tableView_3->horizontalHeader();

    header->setStretchLastSection(true);

    ui->tableView_3->setHorizontalHeader(header);
    ui->tableView_3->resizeRowsToContents();


}
void Journal::on_tableView_activated(const QModelIndex &index)
{
    QString data = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    qDebug()<<data.toInt();
    curJourn = data;
    QString data2 = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
    qDebug()<<data2;
     curJournName = data2;

    setVolumeView(data);
}

void Journal::on_tableView_2_activated(const QModelIndex &index)
{
    QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(),0)).toString();
    setIssueView(data);
}

void Journal::on_tableView_3_clicked(const QModelIndex &index)
{
    ui->tableView_3->selectRow(index.row());
}

void Journal::on_tableView_3_activated(const QModelIndex &index)
{
    QString data = ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),0)).toString();
    curIssue = data;



}

void Journal::on_toolButton_5_clicked()
{
    addVolume *av = new addVolume;
    av->setJournalDets(curJourn,curJournName);
   int retCode= av->exec();
    //if accepted then reset view for volume of current journal
    if(retCode==1) setVolumeView(curJourn);
    connect(av,SIGNAL(destroyed()),av,SLOT(deleteLater()));
}

void Journal::on_toolButton_6_clicked()
{

}
