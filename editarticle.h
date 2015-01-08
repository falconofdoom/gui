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

    void on_removeAuthor_clicked();

private:
    Ui::editarticle *ui;
    QStandardItemModel *model;
};

#endif // EDITARTICLE_H
