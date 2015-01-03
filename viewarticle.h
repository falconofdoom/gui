#ifndef VIEWARTICLE_H
#define VIEWARTICLE_H

#include <QWidget>

namespace Ui {
class ViewArticle;
}

class ViewArticle : public QWidget
{
    Q_OBJECT

public:
    explicit ViewArticle(QWidget *parent = 0);
    ~ViewArticle();

private:
    Ui::ViewArticle *ui;
};

#endif // VIEWARTICLE_H
