#ifndef JOURNAL_H
#define JOURNAL_H

#include <QDialog>

namespace Ui {
class Journal;
}

class Journal : public QDialog
{
    Q_OBJECT

public:
    explicit Journal(QWidget *parent = 0);
    ~Journal();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);


    void on_tableView_2_activated(const QModelIndex &index);

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_tableView_3_activated(const QModelIndex &index);

    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_4_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Journal *ui;
    void setTableView();
    void setTableView(QString arg);
    void setVolumeView(QString index);
    void setIssueView(QString index);
};

#endif // JOURNAL_H
