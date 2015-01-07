#ifndef VIEWARTICLE_H
#define VIEWARTICLE_H

#include <QDialog>

namespace Ui {
class ViewArticle;
}

class ViewArticle : public QDialog
{
    Q_OBJECT

public:
    explicit ViewArticle(QString artID,QWidget *parent = 0);
    QString id;
    ~ViewArticle();

private:
    Ui::ViewArticle *ui;
};

#endif // VIEWARTICLE_H
