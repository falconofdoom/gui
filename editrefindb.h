#ifndef EDITREFINDB_H
#define EDITREFINDB_H

#include <QDialog>

namespace Ui {
class EditRefInDB;
}

/**
 * @brief The EditRefInDB class is a class used to edit
 * bibliographic data already inside the database
 */
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
