#include "articles.h"
#include "ui_articles.h"
#include "QDebug"
#include "utility.h"
#include "QHeaderView"
#include "QModelIndex"
#include "QSqlQuery"
#include "QSqlError"
#include "editarticle.h"
#include "QMessageBox"
#include "viewarticle.h"
Articles::Articles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Articles)
{
    ui->setupUi(this);
    ui->lineEdit->textChanged("");
    curArt="-1";
}

Articles::~Articles()
{
    delete ui;
}

void Articles::journalSetup(QString entry)
{
    sqlmodel = new QSqlQueryModel;
    QString wcard = entry;
    QString queryString = QString("SELECT * FROM JOURNAL WHERE NAME LIKE '\%%1\%'").arg(wcard);
    sqlmodel->setQuery(queryString);

    sqlmodel->setHeaderData(1,Qt::Horizontal,tr("Journal"));
    ui->journalTable->setModel(sqlmodel);

    ui->journalTable->resizeColumnsToContents();
    QHeaderView* header2 = ui->journalTable->horizontalHeader();

    header2->setStretchLastSection(true);

    ui->journalTable->setHorizontalHeader(header2);
    ui->journalTable->setColumnHidden(0,true);
}

void Articles::on_lineEdit_textChanged(const QString &arg1)
{
    journalSetup(ui->lineEdit->text());
}

void Articles::on_journalTable_clicked(const QModelIndex &index)
{

    QString journID = ui->journalTable->model()->
            data(ui->journalTable->model()->index(index.row(),0)).toString();
    QString data2 = ui->journalTable->model()->
            data(ui->journalTable->model()->index(index.row(),1)).toString();
     curJournName = data2;
     curJourn = journID;

     QSqlQueryModel *vol = new QSqlQueryModel;
     QString volquery =
                    "SELECT volume FROM journal_volume"+
                    QString(" where journal_id=%1 order by volume DESC")
                    .arg(journID);
     vol->setQuery(volquery);
     ui->vComboBox->setModel(vol);

     setArticleTable();
     curArt="-1";

}


void Articles::on_vComboBox_currentTextChanged(const QString &arg1)
{

    QString volData = ui->vComboBox->currentText();
    curVol = volData;
    QSqlQueryModel *issue = new QSqlQueryModel;
    QString issuequery = QString("SELECT issue FROM journal_issue where journal_id=%1 and volume=%2 order by issue DESC")
                        .arg(curJourn).arg(volData);
    issue->setQuery(issuequery);
    ui->iComboBox->setModel(issue);

    setArticleTable();
    curArt="-1";

}

void Articles::on_iComboBox_currentTextChanged(const QString &arg1)
{
    curIssue = ui->iComboBox->currentText();

    QString queryString2 =

     QString("SELECT month,year FROM journal_issue WHERE journal_id = %1 and volume = %2 and issue = %3")
            .arg(curJourn).arg(curVol).arg(curIssue);
    QSqlQuery qry;
    qry.prepare(queryString2);

    if (!qry.exec() || !qry.first())
    {
       qDebug() << qry.lastError().text();
       ui->month->setText("Month: ");
       ui->year->setText("Year: ");
    }
    else
    {
         int month = qry.value(0).toInt();
         int year = qry.value(1).toInt();

         ui->month->setText(QString("Month: %1").arg( Utility::intToMonth(month)));
         ui->year->setText(QString("Year: %1").arg(year));

    }

    setArticleTable();
}

void Articles::on_viewArticleButton_clicked()
{
    if(curArt != "-1"){
        ViewArticle *vA = new ViewArticle(curArt);
        vA->exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.critical(0,"Error","No article selected, please select and try again");
        msgBox.setFixedSize(500,200);
    }
}

void Articles::on_articleTable_clicked(const QModelIndex &index)
{
   curArt = sqlmodel->data(sqlmodel->index(index.row(),0)).toString();
}

void Articles::on_delArticleButton_clicked()
{
    if(curArt != "-1"){
        QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Delete Issue",
                             "Are you sure you want to delete this article?" +
                             QString(
                             "This will delete associated parsed citations"),
                              QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            QString delArticle = "DELETE from article where id = " + curArt;
            QString delCitation = "DELETE from citation where article_id = " +
                                  curArt;
            QSqlQuery delQuery1;
            delQuery1.exec(delArticle);
            delQuery1.exec(delCitation);
            setArticleTable();
        }

    }
    else
    {
        QMessageBox msgBox;
        msgBox.critical(0,"Error","No article selected, please select and try again");
        msgBox.setFixedSize(500,200);
    }
}

void Articles::setArticleTable()
{
    sqlmodel = new QSqlQueryModel;
    QString queryString = QString("SELECT * FROM article WHERE journal_id = %1 and volume_id = %2 and issue_id = %3")
                          .arg(curJourn).arg(curVol).arg(curIssue);
    sqlmodel->setQuery(queryString);

    sqlmodel->setHeaderData(1,Qt::Horizontal,tr("Articles"));
    ui->articleTable->setModel(sqlmodel);

    ui->articleTable->resizeColumnsToContents();
    QHeaderView* header3 = ui->articleTable->horizontalHeader();

    header3->setStretchLastSection(true);

    ui->articleTable->setHorizontalHeader(header3);
    ui->articleTable->setColumnHidden(0,true);
    ui->articleTable->setColumnHidden(2,true);
    ui->articleTable->setColumnHidden(3,true);
    ui->articleTable->setColumnHidden(4,true);
    ui->articleTable->setColumnHidden(5,true);
    ui->articleTable->setColumnHidden(6,true);

    curArt="-1";
}

void Articles::on_editArticleButton_clicked()
{
    if(curArt != "-1"){
        EditArticle *eA = new EditArticle(curArt);
        eA->exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.critical(0,"Error","No article selected, please select and try again");
        msgBox.setFixedSize(500,200);
    }
}

void Articles::on_articleTable_activated(const QModelIndex &index)
{
    if(curArt != "-1"){
        ViewArticle *vA = new ViewArticle(curArt);
        vA->exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.critical(0,"Error","No article selected, please select and try again");
        msgBox.setFixedSize(500,200);
    }
}
