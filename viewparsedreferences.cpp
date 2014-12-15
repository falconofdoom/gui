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

    ui->lineEdit->textChanged("");


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
    qry.exec(QString("SELECT * from citation where article_id = %1").arg(data.toInt()));
    qDebug()<<QString("SELECT * from citation where article_id = %1").arg(data.toInt());
    QWidget *central = new QWidget;
    ui->scrollArea->layout()->deleteLater();
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
        errcount.push_back(qry.value(2).toInt());
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

void ViewParsedReferences::journalSetup(QString entry)
{
    sqlmodel = new QSqlQueryModel;
    QString wcard = entry;
    QString queryString = QString("SELECT * FROM JOURNAL WHERE NAME LIKE '\%%1\%'").arg(wcard);
    sqlmodel->setQuery(queryString);

    sqlmodel->setHeaderData(1,Qt::Horizontal,tr("Journal"));
    ui->tableView_2->setModel(sqlmodel);

    ui->tableView_2->resizeColumnsToContents();
    QHeaderView* header2 = ui->tableView_2->horizontalHeader();

    header2->setStretchLastSection(true);

    ui->tableView_2->setHorizontalHeader(header2);
    ui->tableView_2->resizeRowsToContents();
    ui->tableView_2->setColumnHidden(0,true);
}

void ViewParsedReferences::on_lineEdit_textChanged(const QString &arg1)
{
   journalSetup( ui->lineEdit->text());
}

void ViewParsedReferences::on_tableView_2_clicked(const QModelIndex &index)
{
    QString journID = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(),0)).toString();
    QString data2 = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(),1)).toString();
    qDebug()<<data2;
     curJournName = data2;
     curJourn = journID;

     QSqlQueryModel *vol = new QSqlQueryModel;
     QString volquery = QString("SELECT volume FROM journal_volume where journal_id=%1").arg(journID);
     vol->setQuery(volquery);
     ui->comboBox->setModel(vol);
}

void ViewParsedReferences::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString volData = ui->comboBox->currentText();
    curVol = volData;
    QSqlQueryModel *issue = new QSqlQueryModel;
    QString issuequery = QString("SELECT issue FROM journal_issue where journal_id=%1 and volume=%2").arg(curJourn).arg(volData);
    issue->setQuery(issuequery);
    ui->comboBox_2->setModel(issue);
    qDebug()<<issuequery;
}

void ViewParsedReferences::on_comboBox_2_currentTextChanged(const QString &arg1)
{

    curIssue = ui->comboBox_2->currentText();
    sqlmodel = new QSqlQueryModel;
    QString queryString = QString("SELECT * FROM article WHERE journal_id = %1 and volume_id = %2 and issue_id = %3").arg(curJourn).arg(curVol).arg(curIssue);
    sqlmodel->setQuery(queryString);

    sqlmodel->setHeaderData(1,Qt::Horizontal,tr("Articles"));
    ui->tableView->setModel(sqlmodel);

    ui->tableView->resizeColumnsToContents();
    QHeaderView* header3 = ui->tableView->horizontalHeader();

    header3->setStretchLastSection(true);

    ui->tableView->setHorizontalHeader(header3);
    ui->tableView->resizeRowsToContents();
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(2,true);
    ui->tableView->setColumnHidden(3,true);
    ui->tableView->setColumnHidden(4,true);
    ui->tableView->setColumnHidden(5,true);
    ui->tableView->setColumnHidden(6,true);

    qDebug()<<queryString;
}
