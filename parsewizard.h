#ifndef PARSEWIZARD_H
#define PARSEWIZARD_H

#include <QWizard>
#include "QStandardItemModel"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "editparsedreferences.h"
#include "QLineEdit"
#include "QSet"
namespace Ui {
class parseWizard;
}

/**
 * @brief The ParseWizard class is used for data
 * capture and bibliographic data extraction (AGMs)
 *
 */

class ParseWizard : public QWizard
{
    Q_OBJECT

public:
    explicit ParseWizard(QWidget *parent = 0);
    ~ParseWizard();
    QVector <int> errCount; // error count
    QVector < QPushButton * > qpb; // vector of push button identifier of AGms
    QVector < QVector < QString > > vvqs;
    QMap < QString, QString > parseMap; // maps parser names to file path
    QVector < QLineEdit* > vqle1; // lineedit for editing data fields of AGM
    QVector < QLineEdit *> vqle2; // lineedit for editing data fields of AGM
    QVector < QToolButton *> vqtb; //tool button for deleting data field of AGM
    QGridLayout *qgrid; // grid layout of editing window of AGM not saved to db
    EditParsedReferences *editwidget; // editing window of AGM not saved to db
    int proxtotal; // temporary error count unless committed
    QSet < QLineEdit * > modifiedLine; // checks if data field was edited
    QVector <bool> vAddedRow; // checks to see if row was added
    QPushButton *ok; // confirmation for editing window of AGM
    QPushButton *cancel; // cancel for editing window of AGM
    QPushButton *addrow; // adds rows
private slots:

    /**
     * @brief on_lineEdit_2_textChanged implements a search bar
     * to easily access a journal from the journal table
     * @param arg1
     */
    void on_lineEdit_2_textChanged(const QString &arg1);

    /**
     * @brief on_journalTable_clicked changes data in combobox
     * for volume and issue
     * @param index
     */
    void on_journalTable_clicked(const QModelIndex &index);

    /**
     * @brief on_comboBox_currentTextChanged changes data in
     * combobox for issue
     * @param arg1
     */
    void on_comboBox_currentTextChanged(const QString &arg1);

    /**
     * @brief on_pushButton_3_clicked clears textEdit for
     * reference data
     */
    void on_pushButton_3_clicked();

    /**
     * @brief on_pushButton_2_clicked sets textEdit of
     * reference data to whatever is in the uploaded file
     */
    void on_pushButton_2_clicked();

    /**
     * @brief on_parseWizard_currentIdChanged used to implement
     * checks and hooks of input fields as each page is navigated
     * @param id
     */
    void on_parseWizard_currentIdChanged(int id);

    /**
     * @brief viewPage sets textbrowser at end of wizard to the
     * current selected AGM
     * @param id
     */
    void viewPage(int id);

    /**
     * @brief editPage opens editing window for editing AGMs
     */
    void editPage();

    /**
     * @brief addError increments error count for a AGM (proxtotal)
     */
    void addError();


    /**
     * @brief commitError commits proxtotal by saving to errCount
     */
    void commitError();

    /**
     * @brief eraseError resets proxtotal
     */
    void eraseError();

    /**
     * @brief on_parseWizard_accepted commits all data inputted
     * to the database
     */
    void on_parseWizard_accepted();
    \
    /**
     * @brief deleteRow deletes row
     * @param row
     */
    void deleteRow(int row);

    /**
     * @brief on_addAuthor_clicked opens the add author window and
     * saves it to the author table depending if the form was accepted
     * or rejected
     */
    void on_addAuthor_clicked();

    /**
     * @brief on_deleteAuthor_clicked removes author from author table
     *
     */
    void on_deleteAuthor_clicked();

    /**
     * @brief addRow adds data field to agm
     */
    void addRow();

private:
    Ui::parseWizard *ui;
    QStandardItemModel *model; // model container for authors
    QSqlQueryModel *sqlmodel;
    int editIndex;
    bool outputClicked; //check for editing current citation was clicked
    bool flagDone; // if parsing was done

};

#endif // PARSEWIZARD_H
