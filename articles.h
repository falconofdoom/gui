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

    QSqlQueryModel *sqlmodel; //will be used to setup article table
    ~Articles();
    QString curJourn;
    QString curJournName;
    QString curVol; // Current Volume
    QString curIssue;
    QString curArt;  //Current Article

private slots:

    /**
     * @brief on_lineEdit_textChanged is an implementation of
     * a dynamic search bar
     * @param arg1
     */
    void on_lineEdit_textChanged(const QString &arg1);

    /**
     * @brief on_journalTable_clicked loads and changes
     * vComboBox's contents(volumes)
     * @param index
     */
    void on_journalTable_clicked(const QModelIndex &index);

    /**
     * @brief on_vComboBox_currentTextChanged is triggered
     * to change the contents of iComboBox(issues)
     * @param arg1
     */
    void on_vComboBox_currentTextChanged(const QString &arg1);

    /**
     * @brief on_iComboBox_currentTextChanged is triggered when
     * an issue is chosen.
     * @param arg1
     */
    void on_iComboBox_currentTextChanged(const QString &arg1);

    /**
     * @brief on_viewArticleButton_clicked opens view Articles window
     */
    void on_viewArticleButton_clicked();

    /**
     * @brief on_articleTable_clicked
     * @param index
     */
    void on_articleTable_clicked(const QModelIndex &index);

    /**
     * @brief on_delArticleButton_clicked prompts a user if an article
     * should be deleted.
     */
    void on_delArticleButton_clicked();\

    /**
     * @brief setArticleTable sets up the tableview for viewing articles
     */
    void setArticleTable();

    /**
     * @brief on_editArticleButton_clicked opens an editing window for
     * the currently selected article
     */
    void on_editArticleButton_clicked();

    /**
     * @brief on_articleTable_activated functions similar to
     * on_viewArticleButton_clicked();
     * @param index
     */
    void on_articleTable_activated(const QModelIndex &index);

private:
    Ui::Articles *ui;
};

#endif // ARTICLES_H
