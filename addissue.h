#ifndef ADDISSUE_H
#define ADDISSUE_H

#include <QDialog>

namespace Ui {
class addIssue;
}

/**
 * @brief The AddIssue class is a container used to add new issues in a journal
 */

class AddIssue : public QDialog
{
    Q_OBJECT

public:
    explicit AddIssue(QWidget *parent = 0);
    /**
     * @brief setJournalDets mutator function that sets up
     * prerequisite information for the issue to be added in the
     * database
     * @param jI The id of the journal where the issue belongs to
     * @param jName The name of the journal where the issue belongs to
     * @param vol The volume of the journal the issue belongs to
     */
    void setJournalDets(QString jI,QString jName,QString vol);

    ~AddIssue();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addIssue *ui;
    QString jName; // Journal Name
    QString jIndex; // Journal Index
    QString jVol; // Journal Volume
};

#endif // ADDISSUE_H
