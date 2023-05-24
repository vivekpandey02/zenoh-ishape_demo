#ifndef DDS_DEMO_ISHAPES_WRITER_QOS_HPP_
#define DDS_DEMO_ISHAPES_WRITER_QOS_HPP_

/** @file */

#include <QtWidgets/QtWidgets>
#include <ui_writerQosForm.h>

/**
 * @addtogroup demos_iShapes
 */
/** @{*/

namespace demo { namespace ishapes {
class WriterQosDialog : public QDialog
{
    Q_OBJECT;
public:
    WriterQosDialog();
    virtual ~WriterQosDialog();

public:

public slots:
    virtual void accept();
    virtual void reject();
private:
    Ui::WriterQoS qosForm_;
};
}
}

/** @}*/

#endif /* DDS_DEMO_ISHAPES_WRITER_QOS_HPP_ */
