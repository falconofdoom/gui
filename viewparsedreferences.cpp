#include "viewparsedreferences.h"
#include "ui_viewparsedreferences.h"
#include "QSql"
#include "QtGui"
#include "QtWidgets"
#include "QGridLayout"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QDebug"
#include "QHeaderView"
#include "QSqlError"
#include "utility.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QRadioButton"
#include "QToolButton"

ViewParsedReferences::ViewParsedReferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewParsedReferences)
{
    ui->setupUi(this);

    ui->lineEdit->textChanged("");
    curart=0;
      proxtotal=0;
  }

ViewParsedReferences::~ViewParsedReferences()
{
    delete ui;

}

void ViewParsedReferences::on_tableView_clicked(const QModelIndex &index)
{
    QString data = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    qDebug()<<data.toInt();
    QSqlQuery qry;
    qry.exec(QString("SELECT * from citation where article_id = %1").arg(data.toInt()));
    qDebug()<<QString("SELECT * from citation where article_id = %1").arg(data.toInt());
    QWidget *central = new QWidget;
    ui->scrollArea->layout()->deleteLater();

    layout = new QVBoxLayout(central);
    ui->scrollArea->setWidget(central);
    ui->scrollArea->setWidgetResizable(true);
    int j=0;

    ui->textBrowser->clear();

    QSignalMapper *mapper = new QSignalMapper(this);
    contents.clear();
    errcount.clear();
    vid.clear();
    vvqs.clear();
    while(qry.next())
    {
        QPushButton *pb = new QPushButton;

        pb->setText(QString("Output %1").arg(j+1));

        layout->addWidget(pb);
        contents.push_back(qry.value(1).toString());
        vid.push_back(qry.value(0).toInt());
        errcount.push_back(qry.value(2).toInt());
        connect(pb,SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(pb,j++);
    }

    connect(mapper,SIGNAL(mapped(int)),this,SLOT(viewContent(int)));

    QVector < QString > vq;
    for(int i=0;i<contents.size();i++)
    {
         vq.clear();
         QTextStream out(&contents[i]);

         while(!out.atEnd())
         {
             QString line = out.readLine();
             vq.push_back(line);
         }
         vvqs.push_back(vq);
    }

    connect(mapper,SIGNAL(mapped(int)),this,SLOT(editContent(int)));




}

void ViewParsedReferences::viewContent(int index)
{
    if(ui->label_3->isVisible()==false)
        ui->label_3->show();
    ui->textBrowser->setText(contents[index]);
    curart=vid[index];
    edIndex=index;
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
    ui->tableView_2->setColumnHidden(0,true);
}

void ViewParsedReferences::on_lineEdit_textChanged(const QString &arg1)
{
   journalSetup( ui->lineEdit->text());
   ui->textBrowser->clear();
}

void ViewParsedReferences::on_tableView_2_clicked(const QModelIndex &index)
{
    QString journID = ui->tableView_2->model()->data(ui->tableView_2->
                      model()->index(index.row(),0)).toString();
    QString data2 = ui->tableView_2->model()->data(ui->tableView_2->
                    model()->index(index.row(),1)).toString();
     curJournName = data2;
     curJourn = journID;

     QSqlQueryModel *vol = new QSqlQueryModel;
     QString volquery =
             QString("SELECT volume FROM journal_volume where journal_id=%1")
             .arg(journID);

     vol->setQuery(volquery);
     ui->comboBox->setModel(vol);

     QWidget *central = new QWidget;
     ui->scrollArea->layout()->deleteLater();

     layout = new QVBoxLayout(central);
     ui->scrollArea->setWidget(central);
     ui->scrollArea->setWidgetResizable(true);
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
    ui->textBrowser->clear();
}

void ViewParsedReferences::on_comboBox_2_currentTextChanged(const QString &arg1)
{

    curIssue = ui->comboBox_2->currentText();
    sqlmodel = new QSqlQueryModel;
    qDebug()<<"issue "+ui->comboBox_2->currentText();

    QString queryString;

    if(curIssue != ""){
       queryString =
       QString("SELECT * FROM article WHERE journal_id = %1 and volume_id = %2 and issue_id = %3")
       .arg(curJourn).arg(curVol).arg(curIssue);
    }
    else
      queryString = "SELECT * from article where journal_id = -999";

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

    QString queryString2 = QString("SELECT month,year FROM journal_issue WHERE journal_id = %1 and volume = %2 and issue = %3").arg(curJourn).arg(curVol).arg(curIssue);
    QSqlQuery qry;
    qry.prepare(queryString2);
    if (!qry.exec() || !qry.first())
    {
       qDebug() << qry.lastError().text();
       ui->label_6->setText("Month: ");
       ui->label_7->setText("Year: ");
    }
    else
    {
         int month = qry.value(0).toInt();
         int year = qry.value(1).toInt();

         ui->label_6->setText(QString("Month: %1").arg(month));
         ui->label_7->setText(QString("Year: %1").arg(year));

    }

    ui->textBrowser->clear();
}




void ViewParsedReferences::editContent(int ind){

    editref = new EditRefInDB;
    edIndex=ind;
    proxtotal=errcount[edIndex];

    qgrid = new QGridLayout;

    vqle1.clear();
    vqle2.clear();
    vqtb.clear();
    vAddedRow.clear();
    errorlabel = new QLabel;
    errorlabel->setFixedHeight(15);
    errorlabel->setText(QString("<b>Errors: %1</b>").arg(proxtotal));

    qgrid->addWidget(errorlabel,0,0);
    QSignalMapper *mapper = new QSignalMapper(this);

    for(int i=0;i<vvqs[ind].size();i++)
    {
        QLineEdit *qle1=new QLineEdit;
        QLineEdit *qle2=new QLineEdit;

        QToolButton *qtb = new QToolButton;
        qtb->setIcon(QIcon(QPixmap(":images/minus.png")));
        qtb->setIconSize(QSize(24,24));


        QString line =  vvqs[ind][i];
        int g = line.indexOf(":");
        QString before = line.left(g);
        QString after = line.mid(g+1);

        qle1->setText(before.trimmed());
        qle2->setText(after.trimmed());
        qle1->setFixedWidth(150);

        vqle1.push_back(qle1);
        vqle2.push_back(qle2);
        vqtb.push_back(qtb);
        vAddedRow.push_back(false);

        qgrid->addWidget(qle1,i+1,0);
        qgrid->addWidget(qle2,i+1,1);
        qgrid->addWidget(qtb,i+1,2);


        connect(vqle1[i],SIGNAL(editingFinished()),this,SLOT(addError()));
        connect(vqle2[i],SIGNAL(editingFinished()),this,SLOT(addError()));
        connect(vqtb[i],SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(vqtb[i],i+1);

    }
    connect(mapper,SIGNAL(mapped(int)),this,SLOT(deleteRow(int)));


    ok = new QPushButton;
    ok->setText("Save Changes");
    cancel = new QPushButton;
    cancel->setText("Ignore Changes");

    addrow = new QPushButton;
    addrow->setText("Add Row");

    ok->setFixedWidth(125);
    cancel->setFixedWidth(125);
    addrow->setFixedWidth(125);

    qgrid->addWidget(ok);
    qgrid->addWidget(cancel);
    qgrid->addWidget(addrow);

    editref->setLayout(qgrid);

    connect(ok,SIGNAL(clicked()),editref,SLOT(accept()));
    connect(cancel,SIGNAL(clicked()),editref,SLOT(reject()));
    connect(addrow,SIGNAL(clicked()),this,SLOT(addRow()));

    connect(editref,SIGNAL(accepted()),this,SLOT(commitError()));

    editref->exec();
    connect(editref,SIGNAL(destroyed()),editref,SLOT(deleteLater()));
}

void ViewParsedReferences::addError()
{
    QLineEdit *lineedit = dynamic_cast<QLineEdit*>(sender());
    if(lineedit->isModified()==true){
        if(modifiedLine.find(lineedit)==modifiedLine.end()){
            proxtotal++;
            errorlabel->setText(QString("<b>Errors: %1</b>").arg(proxtotal));
            modifiedLine.insert(lineedit);
   }
   }
 }

void ViewParsedReferences::commitError(){
    vvqs[edIndex].clear();
    for(int i=0;i<vqle1.size();i++)
    {
        if( vqle1[i]->text() != "-1" && vqle1[i]->text().trimmed().length() > 0
                && vqle2[i]->text().trimmed().length() > 0 ){
            QString str1 = vqle1[i]->text();
            QString str2= vqle2[i]->text();
            vvqs[edIndex].push_back(str1.trimmed().append(" : ").append(str2).trimmed());
        }
    }

       QString accum=Utility::accumulate(edIndex,vvqs);

       for(int i=0; i < contents.size();i++)
       {
           contents[i] = Utility::accumulate(i,vvqs);
       }

      QString querystring =
            QString("UPDATE citation set content='%1',errors = %2 where id=%3")
                .arg(accum).arg(proxtotal).arg(vid[edIndex]);
      qDebug()<<querystring;
      QSqlQuery query;
      query.exec(querystring);
      errcount[edIndex]=proxtotal;

     // ui->label_3->setText(QString("No. of Errors: (No output selected yet!)"));
      ui->label_3->setText(QString("No. of Errors: %1").arg(proxtotal));
      proxtotal=0;

     //  ui->textBrowser->clear();
}


void ViewParsedReferences::deleteRow(int row){
    if(vAddedRow[row-1] == false)
    proxtotal++;
    errorlabel->setText(QString("<b>Errors: %1</b>").arg(proxtotal));

    QLayoutItem *item = qgrid->itemAtPosition(row,0);
    item->widget()->hide();
    item = qgrid->itemAtPosition(row,1);
    item->widget()->hide();
    item = qgrid->itemAtPosition(row,2);
    item->widget()->hide();

    vqle1[row-1]->setText("-1");
    vqle2[row-1]->setText("-1");
}



void ViewParsedReferences::addRow(){
    proxtotal++;
    QLineEdit *qle1 = new QLineEdit;
    QLineEdit *qle2 = new QLineEdit;
    qle1->setFixedWidth(150);

    QToolButton *qtb = new QToolButton;
    qtb->setIcon(QIcon(QPixmap(":images/minus.png")));
    qtb->setIconSize(QSize(24,24));

    vqle1.push_back(qle1);
    vqle2.push_back(qle2);
    vqtb.push_back(qtb);
    vAddedRow.push_back(true);

    qgrid->addWidget(qle1,vqle1.size(),0);
    qgrid->addWidget(qle2,vqle2.size(),1);
    qgrid->addWidget(qtb,vqtb.size(),2);
    qgrid->removeWidget(addrow);
    qgrid->addWidget(ok);
    qgrid->addWidget(cancel);
    qgrid->addWidget(addrow);
//    delete qgrid;

    errorlabel->setText(QString("<b>Errors: %1</b>").arg(proxtotal));

//    qgrid = new QGridLayout;
//    qgrid->addWidget(errorlabel,0,0);

      QSignalMapper *mapper = new QSignalMapper(this);


      connect(qtb,SIGNAL(clicked()),mapper,SLOT(map()));
      mapper->setMapping(qtb,vqtb.size());




    connect(mapper,SIGNAL(mapped(int)),this,SLOT(deleteRow(int)));

}


void ViewParsedReferences::on_editButton_clicked()
{
    qDebug()<<edIndex;
    if( (errcount.size() > 0 || vvqs.size() > 0) && edIndex < errcount.size())
        editContent(edIndex);
    else{
        QMessageBox *qmsg = new QMessageBox;
        qmsg->setText("No parsed citation selected!");
        qmsg->setWindowTitle("Error!");
        qmsg->exec();
    }
}
