#include "editreference.h"
#include "ui_editreference.h"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include "QLineEdit"
#include <QDebug>
#include "QModelIndex"
#include "QSpacerItem"
#include "QVBoxLayout"
#include "QTableView"
#include "QSignalMapper"
#include "QPushButton"
#include "QSet"

editreference::editreference(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editreference)
{
    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel;
    proxtotal=0;
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

editreference::~editreference()
{
    delete ui;
}

void editreference::on_tableView_activated(const QModelIndex &index)
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
    errcount.clear();
    contents.clear();
    vvqs.clear();
    vid.clear();
    QSignalMapper *mapper = new QSignalMapper(this);
   while(qry.next())
   {
        QPushButton *qpb = new QPushButton;
        vid.push_back(qry.value(0).toInt());
        contents.push_back(qry.value(1).toString());
        errcount.push_back(qry.value(3).toInt());
        qpb->setText(QString("Output %1").arg(++j));
        layout->addWidget(qpb);

        connect(qpb,SIGNAL( clicked()),mapper,SLOT(map()));
        mapper->setMapping(qpb,j-1);

   }

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

void editreference::editContent(int ind){

    editref = new EditRefInDB;
    edIndex=ind;
    proxtotal=errcount[edIndex];
    qDebug()<<errcount[ind];

    QGridLayout *qgrid = new QGridLayout;



    vqle1.clear();
    vqle2.clear();
    errorlabel = new QLabel;
    errorlabel->setFixedHeight(15);
    errorlabel->setText(QString("<b>Errors: %1</b>").arg(proxtotal));

    qgrid->addWidget(errorlabel,0,0);
    for(int i=0;i<vvqs[ind].size();i++)
    {
         QLineEdit *qle1=new QLineEdit;
        QLineEdit *qle2=new QLineEdit;

       QString line =  vvqs[ind][i];
        int g = line.indexOf(":");
       QString before = line.left(g);
       QString after = line.mid(g+1);
           qle1->setText(before.trimmed());
               qle2->setText(after.trimmed());
    qle1->setFixedWidth(150);

        vqle1.push_back(qle1);
        vqle2.push_back(qle2);

        qgrid->addWidget(qle1,i+1,0);
        qgrid->addWidget(qle2,i+1,1);
        connect(qle1,SIGNAL(editingFinished()),this,SLOT(addError()));
        connect(qle2,SIGNAL(editingFinished()),this,SLOT(addError()));

    }


    QPushButton *ok = new QPushButton;
    ok->setText("OK");
    QPushButton *cancel = new QPushButton;
    cancel->setText("Cancel");

    ok->setFixedWidth(100);
    cancel->setFixedWidth(100);


    qgrid->addWidget(ok);
    qgrid->addWidget(cancel);


    editref->setLayout(qgrid);

    connect(ok,SIGNAL(clicked()),editref,SLOT(accept()));
    connect(cancel,SIGNAL(clicked()),editref,SLOT(reject()));

    connect(editref,SIGNAL(accepted()),this,SLOT(commitError()));

    editref->exec();

    connect(editref,SIGNAL(destroyed()),editref,SLOT(deleteLater()));
}
QString editreference::accumulate(int i)
{
    QString str="";
    if(!vvqs.empty())
    for(int j=0;j<vvqs[i].size();j++)
    {
        if(vvqs[i][j].trimmed()!="" && vvqs[i][j].trimmed()!="\n")
        {
            if(vvqs[i][j].indexOf("\n")==-1)
           str= str.append(vvqs[i][j]).append("\n");
             else
                str = str.append(vvqs[i][j]);
        }
    }
    return str;
}

void editreference::addError()
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

void editreference::commitError(){
    qDebug()<<vid[edIndex];

   //

        for(int i=0;i<vqle1.size();i++)
        {
            QString str1 = vqle1[i]->text();
            QString str2= vqle2[i]->text();
            vvqs[edIndex][i] = str1.trimmed().append(" : ").append(str2).trimmed();
        }
     QString accum=accumulate(edIndex);

    QString querystring = QString("UPDATE citation set content='%1',errors = %2 where id=%3").arg(accum).arg(proxtotal).arg(vid[edIndex]);
  qDebug()<<querystring;
    QSqlQuery query;
    query.exec(querystring);
    errcount[edIndex]=proxtotal;
    proxtotal=0;

}
