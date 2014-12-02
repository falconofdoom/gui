#ifndef PARSEREFERENCEWIZARD_H
#define PARSEREFERENCEWIZARD_H

#include <QWidget>
#include "QWizard"
#include "QWizardPage"
class ParseReferenceWizard : public QWidget
{
    Q_OBJECT
public:
    explicit ParseReferenceWizard(QWidget *parent = 0);

signals:

public slots:
     QWizardPage *CreateIntroWizard();
};

#endif // PARSEREFERENCEWIZARD_H
