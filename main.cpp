#include <ShapesDialog.hpp>
#include <QtWidgets/QApplication>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#ifdef _WIN32
    #include <Windows.h>
#endif
#ifdef TESTBUILD
    #include <QtTest/QtTest>
#endif
/**
 * @addtogroup demos_iShapes ISO C++ DCPS iShapes Demonstrator Application
 * Refer to @ref ishapes_readme for information on building and running
 * this demo.
 */
/** @{*/
/** @dir */
/** @file */
namespace demo { namespace ishapes {
class iShapes : public QApplication {
    public:
        iShapes(int& argc, char ** argv) :
        QApplication(argc, argv) { }
        virtual ~iShapes() { }

        // reimplemented from QApplication so we can throw exceptions in slots
        virtual bool notify(QObject * receiver, QEvent * event)
        {
            try
            {
                return QApplication::notify(receiver, event);
            }
            catch(std::exception& e)
            {
                std::string message = "Exception caught:-\n";
                message += e.what();
                QString qmessage(message.c_str());
                QMessageBox::critical(NULL, "Error", qmessage);
            }
            return false;
        }
};
}}
int main(int argc, char *argv[])
{
    srand(clock());
    demo::ishapes::iShapes app(argc, argv);
    #ifdef TESTBUILD
    Q_INIT_RESOURCE(ishape_qrc);
    #else
    Q_INIT_RESOURCE(ishape);
    #endif

    int retval;
    try
    {
        demo::ishapes::ShapesDialog shapes;
        
        if (argc > 1) 
            shapes.setConfiguration(argv[1]);
        else
            shapes.setConfiguration();
        
            // Start publishing a circle with default QoS
                #ifdef _WIN32
                FreeConsole();
                #endif
               
                shapes.show();

        retval = app.exec();

    }
    catch(ErrorMessage  e)
    {
        std::string message = "Exception caught:-\n";
        //message += e.what();
        QString qmessage(message.c_str());
        QMessageBox::critical(NULL, "Error", qmessage);
        retval = 1;
    }

    return retval;
}

/** @}*/
