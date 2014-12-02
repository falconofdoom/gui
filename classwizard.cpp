#include <QSqlQuery>
#include <QtGui>
#include <QtWidgets>
#include "classwizard.h"
#include "QWizard"
#include "editparsedreferences.h"
QString inputFile;
QVector < QVector < QString > > vvqs;
QVector < QString > lines;
QVector < QPushButton * > qpb;
QSet < QLineEdit * > modifiedLine;
QVector < QLineEdit* > vqle1;
QVector < QLineEdit *> vqle2;
QTextBrowser *outputBrowser;
QVBoxLayout *qvlayout;
 EditParsedReferences *editwidget;
int editIndex;
QVector <int> errCount;
int proxtotal=0;
bool edit_flag;
QString accumulate(int i)
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


ClassWizard::ClassWizard(QWidget *parent)
    : QWizard(parent)
{
    setWizardStyle(QWizard::ModernStyle);

    setMinimumSize(800,400);
    addPage(new IntroPage);
    addPage(new ClassInfoPage);
    addPage(new ConclusionPage);
    setOption( QWizard::DisabledBackButtonOnLastPage, true );

    setWindowTitle(tr("Parsing Wizard"));
}

void ClassWizard::accept()
{
    QString name = field("outputlabel").toString();
    QString querystring = QString("INSERT INTO reference VALUES(NULL,'%1',1,1,'');").arg(name);
    QSqlQuery query;
    query.exec(querystring);

    QSqlQuery selQuery;

    selQuery.exec("SELECT MAX(id) from reference");
   selQuery.next();
    int id=selQuery.value(0).toInt();

    for(int i=0;i<vvqs.size();i++)
    {
        QString content = accumulate(i);
      QString querystring = QString("INSERT INTO citation VALUES(NULL,'%1',%2,%3);").arg(content).arg(id).arg(errCount[i]);
        query.exec(querystring);
    }

    QDialog::accept();
}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    setWindowTitle("Introduction");

    label = new QLabel(tr("This wizard will help you through the parsing process "
                              "You can input the text needed for the parser, by manually typing "
                              ", copy and pasting, or uploading an input file."
                              "A default label will be assigned to the output, which is editable"
                              " upon preference."));
        label->setWordWrap(true);
        QImage image(":/images/assist.png");
        image=image.scaled(250,250,Qt::IgnoreAspectRatio,Qt::FastTransformation);


        setPixmap(QWizard::WatermarkPixmap,QPixmap::fromImage(image));
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(label);
        setLayout(layout);
}

ClassInfoPage::ClassInfoPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Parsing References"));
    setSubTitle("You can either manually key in, copy and paste, or upload a file containing the raw references and click next, to parse.You will be taken to the output page,where you can make modifications to the output.");
    refLabel = new QLineEdit;
    refInput = new QTextEdit;
    label=new QLabel;
    inputLabel = new QLabel;

    label->setText("Identifier: ");
    inputLabel->setText("Input: ");
    label->setBuddy(refLabel);
    inputLabel->setBuddy(refInput);
    QPushButton *uploadButton = new QPushButton;
    QPushButton *clearButton = new QPushButton;
    uploadButton->setText("Upload File");
    clearButton->setText("Clear Textarea");
    QGridLayout *layout = new QGridLayout;
    QLabel *filler= new QLabel;
    layout->addWidget(label,0,0);
    layout->addWidget(refLabel,0,1);
    layout->addWidget(inputLabel,1,0);
    layout->addWidget(refInput,2,0,1,2);
    layout->addWidget(uploadButton,3,0);
    layout->addWidget(clearButton,3,1);

    registerField("refinput",refInput,"plainText");
    registerField("outputlabel*",refLabel);

    connect( uploadButton,SIGNAL(clicked()),this,SLOT(getInput()));
    connect( clearButton,SIGNAL(clicked()),this,SLOT(clearTextEdit()));


    setLayout(layout);
}


ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    vvqs.clear();
    qpb.clear();

    setTitle(tr("Result"));

    if(!vvqs.empty())
    setSubTitle(QString("Output %1").arg(editIndex+1));
    else
        setSubTitle(QString("NOTHING TO SHOW!"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark2.png"));



}

void ConclusionPage::initializePage()
{
    QString finishText = field("refinput").toString();

    delete this->layout();

    qDebug()<<"FIRST";
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

   // qDebug() << output;
   // ui->textEdit->append(output);

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
   // if(vvqs.size()>0){
    qDebug()<<vvqs.size();
    qpb.clear();
    errCount.clear();
    qpb.resize(vvqs.size());
    errCount.resize(vvqs.size());
    QVBoxLayout *layout = new QVBoxLayout;
    QSignalMapper *mapper = new QSignalMapper(this);
    for(int i=0;i< vvqs.size();i++)
    {
        qpb[i]=new QPushButton;
        qpb[i]->setText(QString("Output %1").arg(i+1));
        layout->addWidget(qpb[i]);
        connect(qpb[i],SIGNAL(clicked()),mapper,SLOT(map()));

        mapper->setMapping(qpb[i],i);
    }
    outputBrowser= new QTextBrowser;
    outputBrowser->setText(accumulate(0));
    QPushButton *pb = new QPushButton;
    pb->setText("Edit");
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(outputBrowser);
    vlayout->addWidget(pb);


    QGridLayout *qgrid = new QGridLayout;
    qgrid->addLayout(layout,0,0);
    qgrid->addLayout(vlayout,0,1);
    setLayout(qgrid);


    connect(mapper,SIGNAL(mapped(int)),this,SLOT(viewPage(int)));
    connect(pb,SIGNAL(clicked()),this,SLOT(editPage()));
    editIndex=0;
 //   }
}

void ConclusionPage::editPage()
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


   editwidget->setLayout(layout);
    connect(editwidget,SIGNAL(accepted()),this,SLOT(commitError()));
    connect(editwidget,SIGNAL(rejected()),this,SLOT(eraseError()));
    viewPage(editIndex);


    if(!errCount.empty())
    editwidget->changeError(errCount[editIndex]);


    editwidget->exec();

}
void ConclusionPage::viewPage(int index)
{
    editIndex=index;
    if(vvqs.size()==0)
        setSubTitle(QString("NOTHING TO SHOW!"));
    else{
    setSubTitle(QString("Output %1\nErrors: %2").arg(editIndex+1).arg(errCount[editIndex]));
    outputBrowser->setText(accumulate(index));

    }
}

void ConclusionPage::commitError()
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

void ConclusionPage::addError()
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

void ClassInfoPage::getInput()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open raw reference file",".","Reference Files (*.in)");
    if( filename.isEmpty())
        return;

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    return;

   refInput->clear();
  QTextStream in(&file);

   while(!in.atEnd())
   {
      QString line = in.readLine();
        refInput->append(line);
   }

}

void ClassInfoPage::clearTextEdit(){
    refInput->clear();
}

void ConclusionPage::eraseError()
{
    proxtotal=0;
}
