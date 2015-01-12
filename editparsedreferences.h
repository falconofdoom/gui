#ifndef EDITPARSEDREFERENCES_H
#define EDITPARSEDREFERENCES_H

#include <QDialog>
#include "QLayout"
#include "QHBoxLayout"
namespace Ui {
class EditParsedReferences;
}

/**
 * @brief The EditParsedReferences class is a class used to edit
 * bibliographic data extracted after parsing.
 */
class EditParsedReferences : public QDialog
{
    Q_OBJECT

public:
    explicit EditParsedReferences(QWidget *parent = 0);
    ~EditParsedReferences();
    /**
     * @brief changeError is a function used to
     * change the layout's error rate
     * @param count
     */
    void changeError(int count);
    QHBoxLayout* horLay();
    void setScrollArea(QLayout *layout);
private:
    Ui::EditParsedReferences *ui;
};






#endif // EDITPARSEDREFERENCES_H
