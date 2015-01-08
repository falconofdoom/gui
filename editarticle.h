#ifndef EDITARTICLE_H
#define EDITARTICLE_H

#include <QDialog>
#include "QStandardItemModel"
#include "QSqlQueryModel"
namespace Ui {
class editarticle;
}

class EditArticle : public QDialog
{
    Q_OBJECT

public:
    explicit EditArticle(QString artID, QWidget *parent = 0);
    ~EditArticle();

private slots:
    void on_addAuthor_clicked();
    void journalSetup(QString entry);
    void on_removeAuthor_clicked();

    void on_searchjournal_textChanged(const QString &arg1);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    Ui::editarticle *ui;
    QStandardItemModel *model;
    QString curJourn;
    QString curArt;
};

#endif // EDITARTICLE_H
