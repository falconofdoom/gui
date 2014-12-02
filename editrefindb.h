#ifndef EDITREFINDB_H
#define EDITREFINDB_H

#include <QDialog>

namespace Ui {
class EditRefInDB;
}

class EditRefInDB : public QDialog
{
    Q_OBJECT

public:
    explicit EditRefInDB(QWidget *parent = 0);
    ~EditRefInDB();
private:
    Ui::EditRefInDB *ui;
};

#endif // EDITREFINDB_H
