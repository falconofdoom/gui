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
    QMap < QString, QString > parseMap;
    QVector < QLineEdit* > vqle1;
    QVector < QLineEdit *> vqle2;
    QVector < QToolButton *> vqtb;
    QGridLayout *qgrid;
    EditParsedReferences *editwidget;
    int proxtotal=0;
    QSet < QLineEdit * > modifiedLine;
    QVector <bool> vAddedRow;
    QPushButton *ok;
    QPushButton *cancel;
    QPushButton *addrow;
    bool flagDone = false;
private slots:
    void on_label_2_linkActivated(const QString &link);

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
    void on_parseWizard_accepted();
    void deleteRow(int row);

    void on_addAuthor_clicked();

    void on_deleteAuthor_clicked();
    void addRow();

private:
    Ui::parseWizard *ui;
    void authorAdded();
    QStandardItemModel *model;
    QSqlQueryModel *sqlmodel;
    int editIndex;


};

#endif // PARSEWIZARD_H
