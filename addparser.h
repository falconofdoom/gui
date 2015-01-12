#ifndef ADDPARSER_H
#define ADDPARSER_H

#include <QDialog>

namespace Ui {
class addParser;
}

/**
 * @brief The addParser class is a container for adding parsers that will
 * be used during the extraction of bibliographic data from article
 * references
 */
class AddParser : public QDialog
{
    Q_OBJECT

public:
    explicit AddParser(QWidget *parent = 0);
    ~AddParser();

private slots:

    /**
     * @brief on_pushButton_clicked is a slot for opening a file dialog box
     * for the parser's path
     */
    void on_pushButton_clicked();

    /**
     * @brief on_buttonBox_accepted confirms the addition of the parser
     * to the system
     */
    void on_buttonBox_accepted();

private:
    Ui::addParser *ui;
};

#endif // ADDPARSER_H
