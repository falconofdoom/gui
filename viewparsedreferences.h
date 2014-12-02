#ifndef VIEWPARSEDREFERENCES_H
#define VIEWPARSEDREFERENCES_H

#include <QDialog>

namespace Ui {
class ViewParsedReferences;
}

class ViewParsedReferences : public QDialog
{
    Q_OBJECT

public:
    explicit ViewParsedReferences(QWidget *parent = 0);
    ~ViewParsedReferences();
    QVector <QString> contents;
    QVector <int> errcount;
    int expindex;
private slots:
    void on_tableView_activated(const QModelIndex &index);
    void viewContent(int index);
    void on_pushButton_clicked();


private:
    Ui::ViewParsedReferences *ui;
};

#endif // VIEWPARSEDREFERENCES_H
