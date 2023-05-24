#ifndef DDS_DEMO_ISHAPES_READER_QOS_HPP_
#define DDS_DEMO_ISHAPES_READER_QOS_HPP_

/** @file */
/**
 * @addtogroup demos_iShapes
 */
/** @{*/


#include <QtWidgets/QtWidgets>
#include <ui_readerQosForm.h>

namespace demo { namespace ishapes {
class ReaderQosDialog : public QDialog
{
    Q_OBJECT;
public:
    ReaderQosDialog();
    virtual ~ReaderQosDialog();


public slots:
    virtual void accept();
    virtual void reject();

private:
    Ui::ReaderQos qosForm_;
};
}
}

/** @}*/

#endif /* DDS_DEMO_ISHAPES_READER_QOS_HPP_ */
