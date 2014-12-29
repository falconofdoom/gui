#ifndef ADDPARSER_H
#define ADDPARSER_H

#include <QDialog>

namespace Ui {
class addParser;
}

class addParser : public QDialog
{
    Q_OBJECT

public:
    explicit addParser(QWidget *parent = 0);
    ~addParser();

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::addParser *ui;
};

#endif // ADDPARSER_H
