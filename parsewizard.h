#ifndef PARSEWIZARD_H
#define PARSEWIZARD_H

#include <QWizard>
#include "QStandardItemModel"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "editparsedreferences.h"
#include "QLineEdit"
#include "QSet"
namespace Ui {
class parseWizard;
}

class parseWizard : public QWizard
{
    Q_OBJECT

public:
    explicit parseWizard(QWidget *parent = 0);
    ~parseWizard();
    QVector <int> errCount;
    QVector < QPushButton * > qpb;
    QVector < QVector < QString > > vvqs;

    QVector < QLineEdit* > vqle1;
    QVector < QLineEdit *> vqle2;
    EditParsedReferences *editwidget;
    int proxtotal=0;
    QSet < QLineEdit * > modifiedLine;

private slots:
    void on_label_2_linkActivated(const QString &link);
    void on_pushButton_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();
    void on_parseWizard_currentIdChanged(int id);
    void viewPage(int id);
    void editPage();
    void addError();
    void commitError();
    void eraseError();
private:
    Ui::parseWizard *ui;
    void authorAdded();
    QStandardItemModel *model;
    QSqlQueryModel *sqlmodel;
    int editIndex;
    QString accumulate(int i);


};

#endif // PARSEWIZARD_H
