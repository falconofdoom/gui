#ifndef PARSERS_H
#define PARSERS_H

#include <QDialog>

namespace Ui {
class parsers;
}

class parsers : public QDialog
{
    Q_OBJECT

public:
    explicit parsers(QWidget *parent = 0);
    ~parsers();

private:
    Ui::parsers *ui;
};

#endif // PARSERS_H
