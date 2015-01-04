#ifndef VIEWPARSEDREFERENCES_H
#define VIEWPARSEDREFERENCES_H

#include <QDialog>
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "editrefindb.h"
#include "QLineEdit"
#include "QLabel"
#include "QSet"
#include "QGridLayout"
namespace Ui {
class ViewParsedReferences;
}

class ViewParsedReferences : public QDialog
{
    Q_OBJECT

public:
    explicit ViewParsedReferences(QWidget *parent = 0);
    ~ViewParsedReferences();
    QVector <QString> contents;
    QVector <int> errcount;
    QVector <int> vid;
    int curart;
    int expindex;
    QSqlQueryModel *sqlmodel;
    QString curJournName;
    QString curJourn;
    QString curVol;
    QString curIssue;
    void journalSetup(QString entry);
    EditRefInDB *editref;
    int edIndex;
    int proxtotal;
    void editContent(int ind);
    QLabel *errorlabel;
    QVector < QVector < QString > > vvqs;
    QVector < QLineEdit* > vqle1;
    QVector < QLineEdit *> vqle2;
    QVector < QToolButton *> vqtb;
    QSet < QLineEdit *> modifiedLine;
    QGridLayout *qgrid;
    int incAddRow = 0;
    int curAddRow = 0;
private slots:

    void addError();
    void addRow();
    void addRowHelper();
    void changeCurRow(int row);
    void changeRowInc(bool flag);
    void commitError();

    void deleteRow(int row);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_2_currentTextChanged(const QString &arg1);
    void on_lineEdit_textChanged(const QString &arg1);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void on_tableView_2_clicked(const QModelIndex &index);
    void viewContent(int index);

private:
    Ui::ViewParsedReferences *ui;

};

#endif // VIEWPARSEDREFERENCES_H
