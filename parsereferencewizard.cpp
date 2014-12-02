#include "parsereferencewizard.h"

ParseReferenceWizard::ParseReferenceWizard(QWidget *parent) :
    QWidget(parent)
{


}

QWizardPage *CreateIntroWizard(){
    QWizardPage *qw = new QWizardPage;

    qw->setTitle("INTRO");

    return qw;
}
