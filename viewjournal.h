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
    explicit ViewJournal(QString jID, QString jName, QString vID
                         , QWidget *parent = 0);
    QString journID;
    QString journName;
    QString volID; // volume ID
    QString issue;
    ~ViewJournal();

private slots:
    void on_issueTable_clicked(const QModelIndex &index);

    /**
     * @brief on_addIssueButton_clicked creates an instance of
     * addIssue and executes that widget
     */
    void on_addIssueButton_clicked();

    /**
     * @brief on_deleteIssueButton_clicked deletes the issue that
     * is currently clicked
     */
    void on_deleteIssueButton_clicked();

    /**
     * @brief on_editIssueButton_clicked opens window for editing issues
     */
    void on_editIssueButton_clicked();

private:
    Ui::viewJournal *ui;
    /**
     * @brief setIssueView sets the row values for issueTable
     */
    void setIssueView();

    /**
     * @brief setLabels sets issue information
     */
    void setLabels();
};

#endif // VIEWJOURNAL_H
