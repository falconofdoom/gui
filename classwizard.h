
#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H

#include <QWizard>
#include <QGridLayout>

class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QTextEdit;

class ClassWizard : public QWizard
{
    Q_OBJECT

public:
    ClassWizard(QWidget *parent = 0);

    void accept();
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

private:
    QLabel *label;
};

class ClassInfoPage : public QWizardPage
{
    Q_OBJECT

public:
    ClassInfoPage(QWidget *parent = 0);

private:
    QTextEdit *refInput;
    QLineEdit *refLabel;\
    QLabel *label;
    QLabel *inputLabel;

public slots:
    void getInput();
    void clearTextEdit();

};

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);
    QGridLayout *qgrid;
protected:
    void initializePage();


private:
    QLabel *label;

public slots:
    void editPage();
    void viewPage(int index);\
    void addError();\
    void commitError();
    void eraseError();
};



#endif
