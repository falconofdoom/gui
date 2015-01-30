#ifndef JOURNAL_H
#define JOURNAL_H

#include <QDialog>

namespace Ui {
class Journal;
}

/**
 * @brief The Journal class for journal management
 */
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
    /**
     * @brief on_toolButton_clicked opens add journal window
     */
    void on_toolButton_clicked();

    /**
     * @brief on_toolButton_3_clicked deletes journals
     */
    void on_toolButton_3_clicked();


    /**
     * @brief on_journalTable_clicked sets volume table data
     * which corresponds to clicked journal
     * @param index
     */
    void on_journalTable_clicked(const QModelIndex &index);

    /**
     * @brief on_toolButton_5_clicked opens the add journal window
     */
    void on_toolButton_5_clicked();


    /**
     * @brief on_toolButton_4_clicked deletes journal volume
     */
    void on_toolButton_4_clicked();

    /**
     * @brief on_lineEdit_textChanged search bar for journals
     * @param arg1
     */
    void on_lineEdit_textChanged(const QString &arg1);


    /**
     * @brief on_volumeTable_clicked highlights journal to which
     * may be deleted
     * @param index
     */
    void on_volumeTable_clicked(const QModelIndex &index);

    /**
     * @brief on_volumeTable_activated for opening issue management window
     * for selected volume
     * @param index
     */
    void on_volumeTable_activated(const QModelIndex &index);

    /**
     * @brief on_editJournButton_clicked open edit journal window
     */
    void on_editJournButton_clicked();

private:
    Ui::Journal *ui;
    void setTableView();
    void setTableView(QString arg);
    void setVolumeView(QString index);
    void setIssueView(QString index);
};

#endif // JOURNAL_H
