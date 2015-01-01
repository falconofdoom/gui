#ifndef VIEWJOURNAL_H
#define VIEWJOURNAL_H

#include <QDialog>

namespace Ui {
class viewJournal;
}

class ViewJournal : public QDialog
{
    Q_OBJECT

public:
    explicit ViewJournal(QString jID, QString jName, QString vID, QWidget *parent = 0);
    QString journID;
    QString journName;
    QString volID;
    QString issue;
    ~ViewJournal();

private slots:
    void on_issueTable_clicked(const QModelIndex &index);

private:
    Ui::viewJournal *ui;
    void setIssueView();
    void setLabels();

};

#endif // VIEWJOURNAL_H
