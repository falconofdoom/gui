#ifndef ARTICLES_H
#define ARTICLES_H

#include <QDialog>
#include <QSqlQueryModel>
#include "QHeaderView"
namespace Ui {
class Articles;
}

class Articles : public QDialog
{
    Q_OBJECT

public:
    explicit Articles(QWidget *parent = 0);
    void journalSetup(QString entry);
    QSqlQueryModel *sqlmodel;
    ~Articles();
    QString curJourn;
    QString curJournName;
    QString curVol;
    QString curIssue;
    QString curArt="-1";
private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

    void on_vComboBox_currentTextChanged(const QString &arg1);

    void on_iComboBox_currentTextChanged(const QString &arg1);

    void on_viewArticleButton_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_delArticleButton_clicked();
    void setArticleTable();
    void on_editArticleButton_clicked();

private:
    Ui::Articles *ui;
};

#endif // ARTICLES_H
