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
    QString curJourn;
    QString curIssue;
    QString curJournName;
    QString curVol;
    ~Journal();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_3_clicked();

    void on_journalTable_clicked(const QModelIndex &index);


    void on_toolButton_5_clicked();


    void on_toolButton_4_clicked();

    void on_lineEdit_textChanged(const QString &arg1);


    void on_volumeTable_clicked(const QModelIndex &index);

    void on_volumeTable_activated(const QModelIndex &index);

    void on_editJournButton_clicked();

private:
    Ui::Journal *ui;
    void setTableView();
    void setTableView(QString arg);
    void setVolumeView(QString index);
    void setIssueView(QString index);
};

#endif // JOURNAL_H
