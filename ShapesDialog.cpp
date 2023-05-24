/**
 * @file
 */
#include "config.hpp"
#include "ShapesDialog.hpp"
#include <QtWidgets/QtWidgets>
#include <iostream>
#include <Circle.hpp>
#include <Square.hpp>
#include <Triangle.hpp>
#include <BouncingShapeDynamics.hpp>
#include <ZenohShapeDynamics.hpp>
#include <sstream>

#include <unistd.h>
using namespace zenoh;

namespace demo { namespace ishapes {
static const float PI = 3.1415926535F;

/* Ugly hack -- fixme */
static QColor  color_[CN];

const char* const colorString_[] =
{
    "BLUE",
    "RED",
    "GREEN",
    "ORANGE",
    "YELLOW",
    "MAGENTA",
    "CYAN",
    "GRAY",
    "BLACK"
};

static const std::string circleTopicName("Circle");
static const std::string squareTopicName("Square");
static const std::string triangleTopicName("Triangle");

#ifdef TESTBUILD
void ShapesDialog::CreatePublisher()
{
    onPublishButtonClicked();
    qDebug("Created Publisher");
}

void ShapesDialog::CreateSubscriber()
{
    onSubscribeButtonClicked();
    qDebug("Created Subscriber");
}

void ShapesDialog::CreatePublisherMMQos()
{
}
void ShapesDialog::CreateSubscriberMMQos(){}

void ShapesDialog::logShape()
{
}
void ShapesDialog::logDDSShape(){}

#endif

static std::string lexicalCast(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

ShapesDialog::ShapesDialog()
    :   timer(this), session(nullptr), pub(nullptr)
{
    mainWidget.setupUi (this);
    shapesWidget = new ShapesWidget(mainWidget.renderFrame);
    shapesWidget->resize(mainWidget.renderFrame->size());
    shapesWidget->installEventFilter(this);
    shapesWidget->setObjectName(QString("renderFrame"));
    mainWidget.PausedLabel->setVisible(false);

    mainWidget.filterButton->setVisible(false);  // For CYCLONE

    //setSession();

	
    filterDialog_ = new FilterDialog(shapesWidget);
    connect(&timer, SIGNAL(timeout()),
            shapesWidget, SLOT(nextAnimationFrame()));

    color_[BLUE] = QColor(0x33, 0x66, 0x99);
    color_[RED] = QColor(0xCC, 0x33, 0x33);
    color_[GREEN] = QColor(0x99, 0xCC, 0x66);
    color_[ORANGE] = QColor(0xFF, 0x99, 0x33);
    color_[YELLOW] = QColor(0xFF, 0xFF, 0x66);
    color_[MAGENTA] = QColor(0xCC, 0x99, 0xCC);
    color_[CYAN] = QColor(0x99, 0xCC, 0xFF);
    color_[GRAY] = QColor(0x99, 0x99, 0x99);
    color_[BLACK] = QColor(0x33, 0x33, 0x33);
    timer.start(40);
}

ShapesDialog::~ShapesDialog()
{
    //pub.delete_resource();
    //session->close();
}

void ShapesDialog::setConfiguration(const char * conf) 
{
    //std::cout<<"conf: "<<conf<<std::endl;
    if(!conf)
    {
        std::cout<<"in default configuration. "<<std::endl;
        Config config;
        Session s = std::get<Session>(zenoh::open(std::move(config)));
        session = std::make_shared<Session>(std::move(s));
    }
    else{

        std::cout<<"from json5 file configuration. file Name: "<<conf<<std::endl;
        Config config = std::get<Config>(config_from_file(conf));
         auto s = std::get<Session>(zenoh::open(std::move(config)));
         session = std::make_shared<Session>(std::move(s));

    }
}

void
ShapesDialog::onPublishButtonClicked()
{

    int d = mainWidget.sizeSlider->value();
    float speed = ((float)mainWidget.speedSlider->value()) / 9;
    QRect rect(0, 0, d, d);
    // TODO: This should be retrieved from the canvas...


    QRect constr(0, 0, IS_WIDTH, IS_HEIGHT);
    int x = constr.width() * ((float)rand() / RAND_MAX);
    int y = constr.height() * ((float)rand() / RAND_MAX);
    int cIdx = mainWidget.colorList->currentIndex();
    int sIdx = mainWidget.wShapeList->currentIndex();

    QBrush brush(color_[cIdx], Qt::SolidPattern);
    QPen pen(QColor(0xff, 0xff, 0xff), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    ShapeType shape;
    shape.color() = colorString_[cIdx];
    shape.shapesize() = rect.width();
    shape.x() = x;
    shape.y() = y;

    switch (sIdx)
    {

        case CIRCLE:
        {
            std::string colorStr(colorString_[cIdx]);
            const std::string& keyExpression = "demo/ishape/shapeType/circle/"+colorStr;
            std::cout<<"keyExpression: "<<keyExpression<<std::endl;
            KeyExprView keyExp(keyExpression);
            Publisher p = std::get<Publisher>(session->declare_publisher(keyExp));

            BouncingShapeDynamics::ref_type dynamics(new BouncingShapeDynamics(x, y, rect, constr, PI/6, speed, shape, std::move(p)));
            Shape::ref_type  circle(new Circle(rect, dynamics, pen, brush));
            shapesWidget->addShape(circle);

            break;
        }

        case SQUARE:
        {

           //Publisher p = std::get<Publisher>(session->declare_publisher("demo/ishape/shapeType/square"));
            std::string colorStr(colorString_[cIdx]);
            const std::string& keyExpression = "demo/ishape/shapeType/square/"+colorStr;
            KeyExprView keyExp(keyExpression);
            Publisher p = std::get<Publisher>(session->declare_publisher(keyExp));

            BouncingShapeDynamics::ref_type dynamics(new BouncingShapeDynamics(x, y, rect, constr, PI/6, speed, shape, std::move(p)));
            Shape::ref_type  square(new Square(rect, dynamics, pen, brush));
            shapesWidget->addShape(square);
            break;
        }
        case TRIANGLE:
        {

            //Publisher p = std::get<Publisher>(session->declare_publisher("demo/ishape/shapeType/triangle"));
            std::string colorStr(colorString_[cIdx]);
            const std::string& keyExpression = "demo/ishape/shapeType/triangle/"+colorStr;
            KeyExprView keyExp(keyExpression);

            Publisher p = std::get<Publisher>(session->declare_publisher(keyExp));
            BouncingShapeDynamics::ref_type dynamics(new BouncingShapeDynamics(x, y, rect, constr, PI/6, speed, shape, std::move(p)));
            Shape::ref_type  triangle(new Triangle(rect, dynamics, pen, brush));
            shapesWidget->addShape(triangle);
            break;
        }
        default:
            break;
    };
}

void
ShapesDialog::onSubscribeButtonClicked()
{


    int d = mainWidget.sizeSlider->value();
    QRect rect(0, 0, d, d);
    QRect constr(0, 0, IS_WIDTH, IS_HEIGHT);
    int x = static_cast<int>(constr.width() * ((float)rand() / RAND_MAX)*0.9F);
    int y = static_cast<int>(constr.height() * ((float)rand() / RAND_MAX)*0.9F);
    int sIdx = mainWidget.rShapeList->currentIndex();
    
    QColor gray = QColor(0x99, 0x99, 0x99);
    QBrush brush(gray, Qt::SolidPattern);

    QPen pen(QColor(0xff,0xff,0xff), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    std::vector<std::string> empty;
    filterParams_ = empty;
    std::string filterS;
    if (filterDialog_->isEnabled())
    {
        QRect rect =  filterDialog_->getFilterBounds();
        std::string x0 = lexicalCast(rect.x());
        std::string x1 = lexicalCast(rect.x() + rect.width() -d);
        std::string y0 = lexicalCast(rect.y());
        std::string y1 = lexicalCast(rect.y() + rect.height() -d);
        filterParams_.push_back(x0);
        filterParams_.push_back(x1);
        filterParams_.push_back(y0);
        filterParams_.push_back(y1);
        filterS = "(x BETWEEN "
            + filterParams_[0]
            + " AND "
            + filterParams_[1]
            + ") AND (y BETWEEN "
            + filterParams_[2]
            + " AND "
            + filterParams_[3]
            + ")";

        if (filterDialog_->filterOutside() == false)
        {
             filterS = "(x < "
                 + filterParams_[0]
                 + " ) OR ( x > "
                 + filterParams_[1]
                 + " ) OR (y < "
                 + filterParams_[2]
                 + ") OR ( y > "
                 + filterParams_[3]
                 + ")";
        }
    }

    //std::cout<<"sIdx: "<<sIdx<<std::endl;
    switch (sIdx)
    {

        case CIRCLE:
        {
	     //std::cout<<"in Circle: "<<sIdx<<std::endl;
            //const std::string& keyExp = "demo/ishape/shapeType/circle";
            //std::vector<std::thread> workers;
            for (int i = 0; i < 8; ++i)
            { 
                    std::string colorStr(colorString_[i]);
                    const std::string& keyExp = "demo/ishape/shapeType/circle/"+colorStr;

                    ZenohShapeDynamics::ref_type
                    dynamics(new ZenohShapeDynamics(x, y, session, keyExp, colorStr, i, true));

                    //dynamics->setSession(session);
                    //dynamics->setSubscriber(keyExp);

                    
                    Shape::ref_type
                    circle(new Circle(rect, dynamics, pen, brush, true));

                    dynamics->setShape(circle);
                    shapesWidget->addShape(circle);
                    
            }
            break;
        }

        case SQUARE:
        {
            //const std::string& keyExp = "demo/ishape/shapeType/square";
            //std::vector<std::thread> workers;
            for (int i = 0; i < 8; ++i)
            {
                    std::string colorStr(colorString_[i]);
                    const std::string& keyExp = "demo/ishape/shapeType/square/"+colorStr;

                    ZenohShapeDynamics::ref_type
                    dynamics(new ZenohShapeDynamics(x, y, session, keyExp, colorStr, i, true));

                    //dynamics->setSession(session);
                    //dynamics->setSubscriber(keyExp);
                    //subList.push_back(std::move(dynamics->setSubscriber(keyExp)));

                    
                    Shape::ref_type
                    square(new Square(rect, dynamics, pen, brush, true));

                    dynamics->setShape(square);
                    shapesWidget->addShape(square);
                    
            }

            break;
        }

        case TRIANGLE:
        {
            //const std::string& keyExp = "demo/ishape/shapeType/triangle";
            //std::vector<std::thread> workers;
            for (int i = 0; i < 8; ++i)
            {
                    std::string colorStr(colorString_[i]);
                    const std::string& keyExp = "demo/ishape/shapeType/triangle/"+colorStr;

                    ZenohShapeDynamics::ref_type
                    dynamics(new ZenohShapeDynamics(x, y, session, keyExp, colorStr, i, true));

                    //dynamics->setSession(session);
                    //dynamics->setSubscriber(keyExp);
                    //subList.push_back(std::move(dynamics->setSubscriber(keyExp)));

                    
                    Shape::ref_type
                    triangle(new Triangle(rect, dynamics, pen, brush, true));

                    dynamics->setShape(triangle);
                    shapesWidget->addShape(triangle);
                    
            }
        break;
        }

        default:
            break;
    }
}

void
ShapesDialog::onReaderQosButtonClicked()
{
    readerQos_.setVisible(true);
}
void
ShapesDialog::onWriterQosButtonClicked()
{
    writerQos_.setVisible(true);
}

void
ShapesDialog::onFilterButtonClicked()
{
    filterDialog_->setVisible(true);
}
}}
