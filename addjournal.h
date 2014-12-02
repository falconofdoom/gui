#ifndef ADDJOURNAL_H
#define ADDJOURNAL_H

#include <QDialog>

namespace Ui {
class AddJournal;
}

class AddJournal : public QDialog
{
    Q_OBJECT

public:
    explicit AddJournal(QWidget *parent = 0);
    ~AddJournal();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddJournal *ui;
};

#endif // ADDJOURNAL_H
