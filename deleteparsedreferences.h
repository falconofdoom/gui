#ifndef DELETEPARSEDREFERENCES_H
#define DELETEPARSEDREFERENCES_H
#include "QSqlQueryModel"
#include <QDialog>
#include <QModelIndex>
namespace Ui {
class DeleteParsedReferences;
}

class DeleteParsedReferences : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteParsedReferences(QWidget *parent = 0);
    ~DeleteParsedReferences();
    QModelIndex delIndex;
     QSqlQueryModel *model;
private slots:
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_clicked();

    void on_DeleteParsedReferences_destroyed();

private:
    Ui::DeleteParsedReferences *ui;
};

#endif // DELETEPARSEDREFERENCES_H
