#ifndef EDITISSUE_H
#define EDITISSUE_H

#include <QDialog>

namespace Ui {
class editIssue;
}

/**
 * @brief The EditIssue class is a container used in editing the
 * information of issues already saved in the database
 */
class EditIssue : public QDialog
{
    Q_OBJECT

public:
    explicit EditIssue(QWidget *parent = 0);
    ~EditIssue();

    /**
     * @brief setJournalDets sets default values for form
     * @param jI
     * @param jName
     * @param vol
     * @param iss
     */
    void setJournalDets(QString jI,QString jName,QString vol, QString iss);
    QString jName; // Journal Name
    QString jIndex; // Journal ID/Index
    QString jVol; // Journal Volume
    QString issueID;
    QString issueNum;
private slots:
    /**
     * @brief on_buttonBox_accepted confirms changes and commits to database
     */
    void on_buttonBox_accepted();

private:
    Ui::editIssue *ui;
};

#endif // EDITISSUE_H
