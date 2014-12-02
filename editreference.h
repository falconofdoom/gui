#ifndef EDITREFERENCE_H
#define EDITREFERENCE_H

#include <QDialog>
#include <QVector>
#include <QSet>
#include <QLineEdit>
#include "editrefindb.h"
#include "QLabel"
namespace Ui {
class editreference;
}

class editreference : public QDialog
{
    Q_OBJECT

public:
    explicit editreference(QWidget *parent = 0);
    ~editreference();
    QVector < QString > contents;
    QVector < QVector < QString > > vvqs;
    QVector < int > errcount;
    QString accumulate(int i);
    QVector <int> vid;
    QSet < QLineEdit *> modifiedLine;
    QVector < QLineEdit *> vqle1;
    QVector < QLineEdit *> vqle2;
 QLabel *errorlabel;
    EditRefInDB *editref;
    int proxtotal;
    int edIndex;
private slots:
    void on_tableView_activated(const QModelIndex &index);
public slots:
    void editContent(int ind);
    void addError();
    void commitError();
private:
    Ui::editreference *ui;
};

#endif // EDITREFERENCE_H
