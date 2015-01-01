#include "addparser.h"
#include "ui_addparser.h"
#include "QFileDialog"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "QMessageBox"
addParser::addParser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addParser)
{
    ui->setupUi(this);
}

addParser::~addParser()
{
    delete ui;
}

void addParser::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Path to parser daemon");
    if( filename.isEmpty())
        return;
    ui->lineEdit_2->clear();
    ui->lineEdit_2->setText(filename);

}

void addParser::on_buttonBox_accepted()
{
    QString parsename = ui->lineEdit_3->text();
    QString filename = ui->lineEdit_2->text();
    QSqlQuery query1;
    QString ins = QString("insert into parser values(NULL,'%1','%2')")
                  .arg(parsename).arg(filename);

    query1.prepare(QString("Select count(*) from parser where path = '%1'")
    .arg(filename));

    // Try to execute the query and position the result on the first and unique record
    if (!query1.exec() || !query1.first())
    {
       // SQL error (for example, if the table doesn't exist)
       qDebug() << query1.lastError().text();
    }
    // value(0) of first record will contain the "count(*)" value
    else if (query1.value(0) == 0)
    {
        QSqlQuery insqry;
        insqry.exec(ins);
        qDebug()<<"Tessqt";
        qDebug() << query1.lastError().text();

    }
    else
    {
         QMessageBox msgBox;
         msgBox.critical(0,"Error","Parser already exists in the database!");
         msgBox.setFixedSize(500,200);
    }
}
