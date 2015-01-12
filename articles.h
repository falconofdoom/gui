#ifndef ARTICLES_H
#define ARTICLES_H

#include <QDialog>
#include <QSqlQueryModel>
#include "QHeaderView"
namespace Ui {
class Articles;
}

/**
 * @brief The Articles class is a class which manages articles saved
 * into the database
 */
class Articles : public QDialog
{
    Q_OBJECT

public:
    explicit Articles(QWidget *parent = 0);
    void journalSetup(QString entry);
    QSqlQueryModel *sqlmodel; // SQL Model which will be
    ~Articles();
    QString curJourn;
    QString curJournName;
    QString curVol; //current volume
    QString curIssue;
    QString curArt; // current article

private slots:

    void on_lineEdit_textChanged(const QString &arg1);


    void on_journalTable_clicked(const QModelIndex &index);

    void on_vComboBox_currentTextChanged(const QString &arg1);

    void on_iComboBox_currentTextChanged(const QString &arg1);

    void on_viewArticleButton_clicked();

    void on_articleTable_clicked(const QModelIndex &index);

    void on_delArticleButton_clicked();
    void setArticleTable();
    void on_editArticleButton_clicked();

    void on_articleTable_activated(const QModelIndex &index);

private:
    Ui::Articles *ui;
};

#endif // ARTICLES_H
