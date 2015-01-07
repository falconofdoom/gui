#ifndef EDITARTICLE_H
#define EDITARTICLE_H

#include <QDialog>

namespace Ui {
class editarticle;
}

class EditArticle : public QDialog
{
    Q_OBJECT

public:
    explicit EditArticle(QString artID, QWidget *parent = 0);
    ~EditArticle();

private:
    Ui::editarticle *ui;
};

#endif // EDITARTICLE_H
