#ifndef EDITISSUE_H
#define EDITISSUE_H

#include <QDialog>

namespace Ui {
class editIssue;
}

class EditIssue : public QDialog
{
    Q_OBJECT

public:
    explicit EditIssue(QWidget *parent = 0);
    ~EditIssue();
    void setJournalDets(QString jI,QString jName,QString vol, QString iss);
    QString jName;
    QString jIndex;
    QString jVol;
    QString issueID;
    QString issueNum;
private slots:
    void on_buttonBox_accepted();

private:
    Ui::editIssue *ui;
};

#endif // EDITISSUE_H
