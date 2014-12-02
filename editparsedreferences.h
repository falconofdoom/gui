#ifndef EDITPARSEDREFERENCES_H
#define EDITPARSEDREFERENCES_H

#include <QDialog>
#include "QHBoxLayout"
namespace Ui {
class EditParsedReferences;
}

class EditParsedReferences : public QDialog
{
    Q_OBJECT

public:
    explicit EditParsedReferences(QWidget *parent = 0);
    ~EditParsedReferences();
    void changeError(int count);
    QHBoxLayout* horLay();

private:
    Ui::EditParsedReferences *ui;
};






#endif // EDITPARSEDREFERENCES_H
