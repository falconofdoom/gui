#include "journal.h"
#include "ui_journal.h"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "addjournal.h"
#include "QDebug"
#include "viewjournal.h"
#include "QMessageBox"
#include "addissue.h"
#include "viewjournal.h"
#include "addvolume.h"

Journal::Journal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Journal)
{
    ui->setupUi(this);
    setTableView();
    setVolumeView("-999");
    this->setWindowTitle("Journal Management");
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
    QModelIndex index = ui->journalTable->currentIndex();



      if(curJourn != ""){
         QMessageBox::StandardButton reply;
         reply =
           QMessageBox::question(this, "Delete Journal",
                           "Are you sure you want to delete this journal," +
                           QString("this will delete associated") +
                           "volumes and issues?",
                           QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::Yes) {

             QString data = ui->journalTable->model()->data(ui->journalTable->model()->
             index(index.row(),0)).toString();
             QSqlQuery delJournal(QString("delete from journal where id = %1")
                              .arg(data));
             delJournal.exec();
             QSqlQuery delVol(
                         QString("delete from journal_volume where journal_id = %1")
                               .arg(data));
             delVol.exec();
             QSqlQuery delIss(
                         QString("delete from journal_issue where journal_id = %1")
                               .arg(data));
             delIss.exec();
             QSqlQuery delArt(
                         QString("delete from article where journal_id = %1")
                               .arg(data));
             delArt.exec();
             setTableView();

         } else {
           qDebug() << "Yes was *not* clicked";
         }
    }
    else
    {
          QMessageBox warning;
          warning.setText("Please click first on a journal of your choosing!");
          warning.setWindowTitle("No Journal Selected");
          warning.exec();
    }


}

void Journal::on_journalTable_clicked(const QModelIndex &index)
{
    ui->journalTable->selectRow(index.row());
    QString data = ui->journalTable->model()->data(ui->journalTable->model()->index(index.row(),0)).toString();
    qDebug()<<data.toInt();
    curJourn = data;
    QString data2 = ui->journalTable->model()->data(ui->journalTable->model()->index(index.row(),1)).toString();
    qDebug()<<data2;
     curJournName = data2;

    setVolumeView(data);
}

void Journal::setTableView(){
    QSqlQueryModel *model = new QSqlQueryModel;

      model->setQuery("SELECT id,name FROM journal");
      model->setHeaderData(0,Qt::Horizontal,tr("ID"));
      model->setHeaderData(1,Qt::Horizontal,tr("Journal Name"));
      ui->journalTable->setModel(model);
      ui->journalTable->verticalHeader()->setVisible(false);


    ui->journalTable->resizeColumnsToContents();
    QHeaderView* header = ui->journalTable->horizontalHeader();

    header->setStretchLastSection(true);
    ui->journalTable->setColumnHidden(0,true);
    ui->journalTable->setHorizontalHeader(header);
}

void Journal::setTableView(QString arg){
    QSqlQueryModel *model = new QSqlQueryModel;
    QString qr = QString("SELECT id,name FROM JOURNAL WHERE NAME LIKE '\%%1\%'").arg(arg);
      model->setQuery(qr);
      model->setHeaderData(0,Qt::Horizontal,tr("ID"));
       model->setHeaderData(1,Qt::Horizontal,tr("Journal Name"));
      ui->journalTable->setModel(model);
      ui->journalTable->verticalHeader()->setVisible(false);


    ui->journalTable->resizeColumnsToContents();
    QHeaderView* header = ui->journalTable->horizontalHeader();

    header->setStretchLastSection(true);

    ui->journalTable->setColumnHidden(0,true);
    ui->journalTable->setHorizontalHeader(header);
    ui->journalTable->resizeRowsToContents();
}
void Journal::setVolumeView(QString index){
    QSqlQueryModel *model = new QSqlQueryModel;

    QString q = QString("SELECT volume FROM journal_volume where journal_id = %1 order by volume DESC")
                .arg(index);
    model->setQuery(q);
    model->setHeaderData(0,Qt::Horizontal,tr("Volume"));
    ui->volumeTable->setModel(model);
    ui->volumeTable->verticalHeader()->setVisible(false);


    ui->volumeTable->resizeColumnsToContents();
    QHeaderView* header = ui->volumeTable->horizontalHeader();

    header->setStretchLastSection(true);

    ui->volumeTable->setHorizontalHeader(header);
    ui->volumeTable->resizeRowsToContents();

}

void Journal::on_toolButton_5_clicked()
{

    if(curJourn!=""){
        AddVolume *av = new AddVolume;
        av->setJournalDets(curJourn,curJournName);
        int retCode= av->exec();
        //if accepted then reset view for volume of current journal
        if(retCode==1) setVolumeView(curJourn);
        connect(av,SIGNAL(destroyed()),av,SLOT(deleteLater()));
    }
    else
    {
        QMessageBox warning;
        warning.setText("Please click first on a journal of your choosing!");
        warning.setWindowTitle("No Journal Selected");
        warning.exec();
    }
}
void Journal::on_toolButton_4_clicked()
{
    QModelIndex index = ui->volumeTable->currentIndex();

    if(curVol!=""){
        QString data = ui->volumeTable->model()->data(ui->volumeTable->
                       model()->index(index.row(),0)).toString();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete Volume",
                "Are you sure you want to delete Volume " + data + " of "
                 +  curJournName +
                 QString(" this will also delete issues associated with it?"),
                 QMessageBox::Yes|QMessageBox::No);

         if (reply == QMessageBox::Yes) {

             QString dvol = QString("delete from journal_volume where volume = %1")
                            .arg(data) + " and journal_id = " + curJourn;
             QSqlQuery delVol(dvol);

             delVol.exec();
             QString diss = QString("delete from journal_issue where volume = %1")
                            .arg(data) + " and journal_id = " + curJourn;
             QSqlQuery delIss(diss);

             delIss.exec();

             QMessageBox success;
             success.setText("The volume has been deleted!");
             success.setWindowTitle("Volume has been deleted");
             success.exec();

             setVolumeView(curJourn);

         } else {
           qDebug() << "Yes was *not* clicked";
         }
    }
    else{
        QMessageBox warning;
        warning.setText("Please click first on the volume you want to delete!");
        warning.setWindowTitle("No Volume Selected");
        warning.exec();
    }
}

void Journal::on_lineEdit_textChanged(const QString &arg1)
{
    setTableView(ui->lineEdit->text());
}



void Journal::on_volumeTable_clicked(const QModelIndex &index)
{
    QString data = ui->volumeTable->model()->data(ui->volumeTable->model()->index(index.row(),0)).toString();
    curVol=data;
}

void Journal::on_volumeTable_activated(const QModelIndex &index)
{
    QString data = ui->volumeTable->model()->data(ui->volumeTable->model()->index(index.row(),0)).toString();
    curVol=data;
    ViewJournal *vj = new ViewJournal(curJourn,curJournName,curVol);

    vj->exec();
}
