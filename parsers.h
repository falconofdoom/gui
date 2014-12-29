#ifndef PARSERS_H
#define PARSERS_H

#include <QDialog>
#include "QSqlQueryModel"
namespace Ui {
class parsers;
}

class parsers : public QDialog
{
    Q_OBJECT

public:
    explicit parsers(QWidget *parent = 0);
    ~parsers();
    QSqlQueryModel *sqlmodel;
private slots:
    void on_pushButton_clicked();
    void setTableView();
private:
    Ui::parsers *ui;
};

#endif // PARSERS_H
