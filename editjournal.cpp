#include "editjournal.h"
#include "ui_editjournal.h"
#include "QSqlQuery"
#include "QMessageBox"
EditJournal::EditJournal(QString jID, QString jName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditJournal)
{
    ui->setupUi(this);

    journID = jID;
    jourName = jName;

    ui->lineEdit->setText(jourName);
}

EditJournal::~EditJournal()
{
    delete ui;
}

void EditJournal::on_buttonBox_accepted()
{
    QString jName = ui->lineEdit->text();

    if( jName.trimmed() != ""){
         QString querystring = QString("UPDATE journal set name = '%1' where id = %2;")
                           .arg(jName).arg(journID);
         QSqlQuery qry;
         qry.exec(querystring);

         QMessageBox success;
         success.setText("Journal was successfully updated!");
         success.setWindowTitle("Journal Updated!");
         success.exec();
     }
     else
     {
        QMessageBox warning;
        warning.setText("Journal name is blank, please fill in the information"
                  + QString("and try again! This transaction will not be saved!"));

        warning.setWindowTitle("No Journal Name");
        warning.exec();
     }
}
