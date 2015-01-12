#ifndef ADDVOLUME_H
#define ADDVOLUME_H

#include <QDialog>

namespace Ui {
class addVolume;
}

/**
 * @brief The AddVolume class is a container which is used in
 * adding volumes to a journal
 */
class AddVolume : public QDialog
{
    Q_OBJECT

public:

    explicit AddVolume(QWidget *parent = 0);
    ~AddVolume();

    /**
     * @brief setJournalDets mutator function which sets prerequisite
     * information for adding a volume to the database
     * @param jI Journal ID
     * @param jN Journal Name
     */
    void setJournalDets(QString jI,QString jN);

private slots:

    /**
     * @brief on_buttonBox_accepted confirmation that the
     * author will be added
     */
    void on_buttonBox_accepted();

private:

    Ui::addVolume *ui;
    QString jIndex; // Journal Index
    QString jName; // Journal Name
};

#endif // ADDVOLUME_H
