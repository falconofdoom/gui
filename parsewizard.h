#ifndef PARSEWIZARD_H
#define PARSEWIZARD_H

#include <QWizard>
#include "QStandardItemModel"
#include "QSqlQueryModel"
#include "QSqlQuery"
namespace Ui {
class parseWizard;
}

class parseWizard : public QWizard
{
    Q_OBJECT

public:
    explicit parseWizard(QWidget *parent = 0);
    ~parseWizard();

private slots:
    void on_label_2_linkActivated(const QString &link);
    void on_pushButton_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

private:
    Ui::parseWizard *ui;
    void authorAdded();
    QStandardItemModel *model;
    QSqlQueryModel *sqlmodel;
};

#endif // PARSEWIZARD_H
