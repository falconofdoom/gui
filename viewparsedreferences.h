#ifndef VIEWPARSEDREFERENCES_H
#define VIEWPARSEDREFERENCES_H

#include <QDialog>
#include "QSqlQueryModel"
#include "QSqlQuery"
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
    int expindex;
    QSqlQueryModel *sqlmodel;
    QString curJournName;
    QString curJourn;
    QString curVol;
    QString curIssue;
    void journalSetup(QString entry);
private slots:
    void on_tableView_activated(const QModelIndex &index);
    void viewContent(int index);
    void on_pushButton_clicked();
    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    Ui::ViewParsedReferences *ui;
};

#endif // VIEWPARSEDREFERENCES_H
