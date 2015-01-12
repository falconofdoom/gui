#ifndef EDITJOURNAL_H
#define EDITJOURNAL_H

#include <QDialog>

namespace Ui {
class EditJournal;
}

class EditJournal : public QDialog
{
    Q_OBJECT

public:
    explicit EditJournal(QString jID, QString jName,QWidget *parent = 0);
    ~EditJournal();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditJournal *ui;
    QString journID;
    QString jourName;
};

#endif // EDITJOURNAL_H
