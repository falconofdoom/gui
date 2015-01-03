#include "viewarticle.h"
#include "ui_viewarticle.h"

ViewArticle::ViewArticle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewArticle)
{
    ui->setupUi(this);
}

ViewArticle::~ViewArticle()
{
    delete ui;
}
