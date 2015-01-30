#ifndef VIEWPARSEDREFERENCES_H
#define VIEWPARSEDREFERENCES_H

#include <QDialog>
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "editrefindb.h"
#include "QLineEdit"
#include "QLabel"
#include "QSet"
#include "QGridLayout"
#include "QVBoxLayout"
namespace Ui {
class ViewParsedReferences;
}

/**
 * @brief The ViewParsedReferences class is a container used to view
 * AGMS already saved into the database
 */
class ViewParsedReferences : public QDialog
{
    Q_OBJECT

public:
    explicit ViewParsedReferences(QWidget *parent = 0);
    ~ViewParsedReferences();
    QVector <QString> contents;
    QVector <int> errcount;
    QVector <int> vid; // id of volumes
    int curart; //current article
    QSqlQueryModel *sqlmodel;
    QString curJournName; // current journal name
    QString curJourn; // current journal id
    QString curVol; // cur volume
    QString curIssue;
    void journalSetup(QString entry);
    EditRefInDB *editref; // edit window for AGM
    int edIndex; // index to be edited
    int proxtotal; // error total, temporary unless committed
    void editContent(int ind);// pop up edit window for currently selected AGM
    QLabel *errorlabel;
    QVector < QVector < QString > > vvqs; // AGMs split into data fields
    QVector < QLineEdit* > vqle1; // will be used to edit data field
    QVector < QLineEdit *> vqle2; // will be used to edit data field value

    QVector < QToolButton *> vqtb; // tool buttons for deleting rows
    QSet < QLineEdit *> modifiedLine; // checks if a data field was modified
    QGridLayout *qgrid; // grid layout for editwindow
    QVBoxLayout *layout; // layout for pushbutton identifier of each agm
    QPushButton *ok; //confirmation button for editing
    QPushButton *cancel; //cancel button for editing
    QPushButton *addrow; // button for adding rows
    QVector <bool> vAddedRow; // checks to see if a row was added

private slots:

    /**
     * @brief addError increments error count
     */
    void addError();

    /**
     * @brief addRow adds a new data field
     */
    void addRow();

    /**
     * @brief commitError saves the error count
     */
    void commitError();

    /**
     * @brief deleteRow removes a data field
     * @param row
     */
    void deleteRow(int row);

    /**
     * @brief on_comboBox_currentTextChanged updates the article table
     * according to volume
     * @param arg1
     */
    void on_comboBox_currentTextChanged(const QString &arg1);
    /**
     * @brief on_comboBox_2_currentTextChanged updates the article table
     * according to issue
     * @param arg1
     */
    void on_comboBox_2_currentTextChanged(const QString &arg1);

    /**
     * @brief on_lineEdit_textChanged search bar for journal table
     * @param arg1
     */
    void on_lineEdit_textChanged(const QString &arg1);

    /**
     * @brief on_pushButton_clicked exports current article as an AGM
     */
    void on_pushButton_clicked();

    /**
     * @brief on_tableView_clicked sets current article based on clicked item
     * @param index
     */
    void on_tableView_clicked(const QModelIndex &index);

    /**
     * @brief on_tableView_2_clicked changes article, combobox data
     * corresponding to current issue
     * @param index
     */
    void on_tableView_2_clicked(const QModelIndex &index);

    /**
     * @brief viewContent fills the textbrowser with currently selected
     * AGM
     * @param index
     */
    void viewContent(int index);

    /**
     * @brief on_editButton_clicked editing window for selecting AGM
     */
    void on_editButton_clicked();

private:
    Ui::ViewParsedReferences *ui;

};

#endif // VIEWPARSEDREFERENCES_H
