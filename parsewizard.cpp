#include "parsewizard.h"
#include "ui_parsewizard.h"
#include "QLabel"
#include "QStandardItem"
#include "QHeaderView"
#include "addauthor.h"
#include "QList"
#include "QDebug"
#include"QMessageBox"
#include "QPushButton"
#include "QFileDialog"
#include "QFile"
#include "QSignalMapper"
#include "editparsedreferences.h"
#include "QProcess"
QString cJourn;

typedef QList< QStandardItem* > StandardItemList;

parseWizard::parseWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::parseWizard)
{

    ui->setupUi(this);


    ui->tableView->alternatingRowColors();
    model = new QStandardItemModel(0,2);
    ui->tableView->setModel(model);

    model->setHeaderData(0,Qt::Horizontal,tr("Author"));
     model->setHeaderData(1,Qt::Horizontal,tr("Affiliation"));
    ui->tableView->setModel(model);


  ui->tableView->resizeColumnsToContents();
  QHeaderView* header = ui->tableView->horizontalHeader();

  for(int i=0;i<header->count();i++)
     header->setSectionResizeMode(i,QHeaderView::Stretch);

  ui->tableView->setHorizontalHeader(header);
  ui->tableView->resizeRowsToContents();

  setOption( QWizard::DisabledBackButtonOnLastPage, true );




  QWidget *central = new QWidget;

  QVBoxLayout *layout = new QVBoxLayout(central);
  ui->scrollArea->setWidget(central);
  ui->scrollArea->setWidgetResizable(true);

}

parseWizard::~parseWizard()
{
    delete ui;
}

void parseWizard::on_label_2_linkActivated(const QString &link)
{

}

void parseWizard::authorAdded()
{
    qDebug()<<"TEST AUTHOR ADDED";
}

QString parseWizard:: accumulate(int i)
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


void parseWizard::on_pushButton_clicked()
{
    addAuthor *aA = new addAuthor;
     int retcode = aA->exec();

     if(retcode==1){
       QStandardItem *auth = new QStandardItem(QString(aA->author));
       QStandardItem *affil = new QStandardItem(QString(aA->affiliation));
       model->appendRow( StandardItemList() << auth << affil );

     }\


    connect(aA,SIGNAL(destroyed()),aA,SLOT(deleteLater()));
}

void parseWizard::on_lineEdit_2_textChanged(const QString &arg1)
{
    sqlmodel = new QSqlQueryModel;
    QString wcard = ui->lineEdit_2->text();
    QString queryString = QString("SELECT * FROM JOURNAL WHERE NAME LIKE '\%%1\%'").arg(wcard);
    sqlmodel->setQuery(queryString);

    sqlmodel->setHeaderData(1,Qt::Horizontal,tr("Journal"));
    ui->tableView_2->setModel(sqlmodel);

    ui->tableView_2->resizeColumnsToContents();
    QHeaderView* header = ui->tableView_2->horizontalHeader();

    header->setStretchLastSection(true);

    ui->tableView_2->setHorizontalHeader(header);
    ui->tableView_2->resizeRowsToContents();
    ui->tableView_2->setColumnHidden(0,true);


}

void parseWizard::on_tableView_2_clicked(const QModelIndex &index)
{
    QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(),0)).toString();
    cJourn=data;
    QSqlQueryModel *vol = new QSqlQueryModel;
    QString volquery = QString("SELECT volume FROM journal_volume where journal_id=%1").arg(data);
    vol->setQuery(volquery);
    ui->comboBox->setModel(vol);
}

void parseWizard::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString volData = ui->comboBox->currentText();
    QSqlQueryModel *issue = new QSqlQueryModel;
    QString issuequery = QString("SELECT issue FROM journal_issue where journal_id=%1 and volume=%2").arg(cJourn).arg(volData);
    issue->setQuery(issuequery);
    ui->comboBox_2->setModel(issue);
    qDebug()<<issuequery;
}

void parseWizard::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
}

void parseWizard::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open raw reference file",".","Reference Files (*.in)");
    if( filename.isEmpty())
        return;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    return;

   ui->textEdit->clear();
  QTextStream in(&file);

   while(!in.atEnd())
   {
      QString line = in.readLine();
        ui->textEdit->append(line);
   }

}
void parseWizard::viewPage(int index)
{
    editIndex=index;
    ui->textEdit_2->setText(accumulate(index));
    ui->label_14->setText(errCount[editIndex]);
}

void parseWizard::on_parseWizard_currentIdChanged(int id)
{
    if(id==4)
    {
      delete ui->scrollArea->layout();
      QString finishText = ui->textEdit->toPlainText();
       QFile file("temp.txt");
       file.open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text);
       QTextStream out(&file);
       out<<finishText;
       file.close();

       QString program = QApplication::applicationDirPath().append("/parser/parserV2");
       QStringList arguments;

       arguments << QString(QApplication::applicationDirPath().append("/temp.txt"));

       QProcess *process = new QProcess(this);
       process->start(program,arguments);
       QMessageBox qmsg;

       if(finishText=="")
           qmsg.setText("PARSING DIDN'T START, BLANK INPUT!!!");
       else if(!process->waitForStarted())
           qmsg.setText("PARSING DIDN'T START");
       else if(!process->waitForFinished())
           qmsg.setText("PARSING DIDN'T FINISH");
       else
           qmsg.setText("PARSING COMPLETE!YOU MAY NOW VIEW OUTPUT!");



       qmsg.exec();
       QString output(process->readAllStandardOutput());
        qDebug()<<output;


        QTextStream qts(&output);
        QVector <QString> vq;
        vq.clear();
        vvqs.clear();
        int count = 0;
        int outputCount=0;


        while(!qts.atEnd())
        {
            QString line = qts.readLine();
            count = 0;
            if(line=="****")
            {
                outputCount++;
                while(line!="####")
                {
                    line = qts.readLine();
                    if(line=="####") break;
                    vq.push_back("");
                    vq[vq.size()-1].append(line);
                    vq[vq.size()-1].append("\n");
                    count++;
                }


             }
            if(vq.size()>=1)
            vvqs.push_back(vq);
            vq.clear();
          }

        qpb.clear();
        errCount.clear();
        qpb.resize(vvqs.size());
        errCount.resize(vvqs.size());
        QVBoxLayout *layout = new QVBoxLayout;
        QSignalMapper *mapper = new QSignalMapper(this);
        for(int i=0;i< qpb.size();i++)
        {
            qpb[i]=new QPushButton;
            qpb[i]->setText(QString("Output %1").arg(i+1));
            layout->addWidget(qpb[i]);
            connect(qpb[i],SIGNAL(clicked()),mapper,SLOT(map()));

            mapper->setMapping(qpb[i],i);
        }
        ui->scrollArea->setLayout(layout
                                  );
        connect(mapper,SIGNAL(mapped(int)),this,SLOT(viewPage(int)));
        connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(editPage()));





    }
}
void parseWizard::editPage()
{
    editwidget=new EditParsedReferences;
    editwidget->setWindowTitle("Edit Parsed References");
    QGridLayout *layout=new QGridLayout;
    int r=0;
    vqle1.clear();
    vqle2.clear();
    QSignalMapper *mapping = new QSignalMapper(this);

    if(!vvqs.empty())
    for(int i=0;i<vvqs[editIndex].size();i++)
    {
        QString line = vvqs[editIndex][i];
        int g = line.indexOf(':');
         QLineEdit *qle = new QLineEdit;
      QLineEdit *lll = new QLineEdit;
        lll->setFixedWidth(150);

        QString before = line.left(g);
        QString after = line.mid(g+1);
            lll->setText(before.trimmed());
                qle->setText(after.trimmed());

                vqle1.push_back(lll);
                vqle2.push_back(qle);
          layout->addWidget(lll,r,0);
         layout->addWidget(qle,r,1);
    connect(lll,SIGNAL(editingFinished()),this,SLOT(addError()));
    connect(qle,SIGNAL(editingFinished()),this,SLOT(addError()));

         r++;
    }


   editwidget->setScrollArea(layout);
    connect(editwidget,SIGNAL(accepted()),this,SLOT(commitError()));
    connect(editwidget,SIGNAL(rejected()),this,SLOT(eraseError()));
    viewPage(editIndex);

    if(!errCount.empty())
    editwidget->changeError(errCount[editIndex]);


    editwidget->exec();
}


void parseWizard::commitError()
{
    errCount[editIndex]+=proxtotal;
    qDebug()<<errCount[editIndex];
    proxtotal=0;
    qDebug()<<" errorCount "<<errCount[editIndex]<<" errorIndex: "<<editIndex;
    qDebug()<<"vvqs_size: "<<vvqs.size();
    for(int i=0;i<vvqs.size();i++)
    qDebug()<<QString("VVQS_[%1]_size: %2").arg(i).arg(vvqs[i].size());
    qDebug()<<"VQLE1_SIZE "<<vqle1.size();
    qDebug()<<"VQLE2_SIZE "<<vqle2.size();
    for(int i=0;i<vqle1.size();i++)
    {
        QString str1 = vqle1[i]->text();
        QString str2= vqle2[i]->text();
        vvqs[editIndex][i] = str1.trimmed().append(" : ").append(str2).trimmed();
    }
    viewPage(editIndex);
}

void parseWizard::addError()
{
    QLineEdit *lineedit = dynamic_cast<QLineEdit*>(sender());
    if(lineedit->isModified()==true){
        if(modifiedLine.find(lineedit)==modifiedLine.end()){
            proxtotal++;
            editwidget->changeError(proxtotal);
            modifiedLine.insert(lineedit);
   }
   }
 }

void parseWizard::eraseError()
{
    proxtotal=0;
}
