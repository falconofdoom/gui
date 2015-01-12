#ifndef ADDJOURNAL_H
#define ADDJOURNAL_H

#include <QDialog>

namespace Ui {
class AddJournal;
}

/**
 * @brief The AddJournal class is a container used for adding new journals to the database
 */
class AddJournal : public QDialog
{
    Q_OBJECT

public:
    explicit AddJournal(QWidget *parent = 0);

    ~AddJournal();

private slots:
    /**
     * @brief on_buttonBox_accepted saves the journal
     */
    void on_buttonBox_accepted();

private:
    Ui::AddJournal *ui;
};

#endif // ADDJOURNAL_H
