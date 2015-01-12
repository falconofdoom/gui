#ifndef PARSERS_H
#define PARSERS_H

#include <QDialog>
#include "QSqlQueryModel"

namespace Ui {
    class parsers;
}

/**
 * @brief The parsers class is used to show the parsers saved in the database
 */
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
    void on_addParser_clicked();

    void on_delParser_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::parsers *ui;
};

#endif // PARSERS_H
