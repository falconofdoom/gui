#ifndef ADDAUTHOR_H
#define ADDAUTHOR_H

#include <QDialog>

namespace Ui {
class addAuthor;
}

/**
 * @brief The addAuthor class is a container for adding authors to an article
 */
class AddAuthor : public QDialog
{
    Q_OBJECT

public:
    explicit AddAuthor(QWidget *parent = 0);
    QString author; // The article author
    QString affiliation; // The affiliation of the article author
    ~AddAuthor();

private slots:

    /**
     * @brief on_buttonBox_accepted passes the value of author and affiliation
     * to the class that called it mainly ParseWizard and EditArticle
     */
    void on_buttonBox_accepted();

private:
    Ui::addAuthor *ui;
};

#endif // ADDAUTHOR_H
