#ifndef EDITARTICLE_H
#define EDITARTICLE_H

#include <QDialog>

namespace Ui {
class editarticle;
}

class editarticle : public QDialog
{
    Q_OBJECT

public:
    explicit editarticle(QWidget *parent = 0);
    ~editarticle();

private:
    Ui::editarticle *ui;
};

#endif // EDITARTICLE_H
