#ifndef ADDVOLUME_H
#define ADDVOLUME_H

#include <QDialog>

namespace Ui {
class addVolume;
}


class addVolume : public QDialog
{
    Q_OBJECT

public:
    explicit addVolume(QWidget *parent = 0);
    ~addVolume();
    void setJournalDets(QString jI,QString jN);
    QString jIndex;
    QString jName;
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_destroyed();

private:
    Ui::addVolume *ui;
};

#endif // ADDVOLUME_H
