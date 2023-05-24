/**
 * @file
 */
#include <WriterQosDialog.hpp>
#include <iostream>

namespace demo { namespace ishapes {

WriterQosDialog::WriterQosDialog()
{
    qosForm_.setupUi(this);
    this->setVisible(false);
    #ifdef Cyclone
    	qosForm_.durabilityComboBox->removeItem(3);
    	qosForm_.durabilityComboBox->removeItem(2);
    #endif
}

WriterQosDialog::~WriterQosDialog() { }

void
WriterQosDialog::accept()
{
    this->setVisible(false);
}

void
WriterQosDialog::reject()
{
    this->setVisible(false);
}

}}
