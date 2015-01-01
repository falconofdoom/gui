#ifndef ADDISSUE_H
#define ADDISSUE_H

#include <QDialog>

namespace Ui {
class addIssue;
}

class AddIssue : public QDialog
{
    Q_OBJECT

public:
    explicit AddIssue(QWidget *parent = 0);
    void setJournalDets(QString jI,QString jName,QString vol);
    QString jName;
    QString jIndex;
    QString jVol;
    ~AddIssue();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addIssue *ui;
};

#endif // ADDISSUE_H
