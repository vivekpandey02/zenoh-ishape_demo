/**
 * @file
 */
#include <ReaderQosDialog.hpp>
#include <iostream>

namespace demo { namespace ishapes {

ReaderQosDialog::ReaderQosDialog()
{
    qosForm_.setupUi(this);
    this->setVisible(false);
    #ifdef Cyclone
    	qosForm_.durabilityComboBox->removeItem(3);
    	qosForm_.durabilityComboBox->removeItem(2);
	qosForm_.groupBox_3->setVisible(false);
    #endif
}

ReaderQosDialog::~ReaderQosDialog() { }

void
ReaderQosDialog::accept()
{
    this->setVisible(false);
}

void
ReaderQosDialog::reject()
{
    this->setVisible(false);
}

}
}
