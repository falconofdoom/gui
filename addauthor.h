#ifndef ADDAUTHOR_H
#define ADDAUTHOR_H

#include <QDialog>

namespace Ui {
class addAuthor;
}

class addAuthor : public QDialog
{
    Q_OBJECT

public:
    explicit addAuthor(QWidget *parent = 0);
    QString author;
    QString affiliation;
    ~addAuthor();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addAuthor *ui;
};

#endif // ADDAUTHOR_H
