#include "viewparsedreferences.h"
#include "ui_viewparsedreferences.h"
#include "QSql"
#include "QtGui"
#include "QtWidgets"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QDebug"
#include "QHeaderView"

ViewParsedReferences::ViewParsedReferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewParsedReferences)
{
    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel;

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

ViewParsedReferences::~ViewParsedReferences()
{
    delete ui;

}

void ViewParsedReferences::on_tableView_activated(const QModelIndex &index)
{
    QString data = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    qDebug()<<data.toInt();
    QSqlQuery qry;
    qry.exec(QString("SELECT * from citation where reference_id='%1'").arg(data.toInt()));

    QWidget *central = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout(central);
    ui->scrollArea->setWidget(central);
    ui->scrollArea->setWidgetResizable(true);
    int j=0;



    QSignalMapper *mapper = new QSignalMapper(this);
    contents.clear();
    errcount.clear();

    while(qry.next())
    {
        QPushButton *pb = new QPushButton;

        pb->setText(QString("Output %1").arg(j+1));

        layout->addWidget(pb);
        contents.push_back(qry.value(1).toString());
        errcount.push_back(qry.value(3).toInt());
        connect(pb,SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(pb,j++);
    }

    connect(mapper,SIGNAL(mapped(int)),this,SLOT(viewContent(int)));

}

void ViewParsedReferences::viewContent(int index)
{
    if(ui->label_3->isVisible()==false)
        ui->label_3->show();
    ui->textBrowser->setText(contents[index]);
    ui->label_3->setText(QString("No. of Errors: %1").arg(errcount[index]));

  }

void ViewParsedReferences::on_pushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,"Export AGM",".","A Good Markup File (*.agm)");
    QFile file(filename.append(".agm"));

    file.open(QIODevice::WriteOnly|QIODevice::Text);

    QTextStream out(&file);

    for(int i=0;i<contents.size();i++)
        out<<contents[i]<<"\n****\n";

}
