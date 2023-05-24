/**
 * @file
 */
#include "ZenohShapeDynamics.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
// including JsonCpp header file
#include <jsoncpp/json/json.h>
#include "config.hpp"
#include <unistd.h>
//include "ishape.hpp"

using namespace std;
using namespace zenoh;


namespace demo { namespace ishapes {
extern char* colorString_[];

//        sub_(nullptr),
ZenohShapeDynamics::ZenohShapeDynamics(int x0, int y0,
                                    std::shared_ptr<Session> session,
                                    const std::string& keyExpression,
                                    const std::string& color,
                                    int colorIdx, bool dummy)
    :   ShapeDynamics(x0, y0, QRect(0, 0, 0, 0)),
        x0_(x0),
        y0_(y0),
        session_(std::move(session)),
        keyexpr_(keyExpression),
        attached_(false),
        color_(color),
        colorIdx_(colorIdx),
        updateBounds_(true),
        dummy_(dummy),
        subscriber_(nullptr)
{

    colorList_[BLUE] = QColor(0x33, 0x66, 0x99);
    colorList_[RED] = QColor(0xCC, 0x33, 0x33);
    colorList_[GREEN] = QColor(0x99, 0xCC, 0x66);
    colorList_[ORANGE] = QColor(0xFF, 0x99, 0x33);
    colorList_[YELLOW] = QColor(0xFF, 0xFF, 0x66);
    colorList_[MAGENTA] = QColor(0xCC, 0x99, 0xCC);
    colorList_[CYAN] = QColor(0x99, 0xCC, 0xFF);
    colorList_[GRAY] = QColor(0x99, 0x99, 0x99);
    colorList_[BLACK] = QColor(0x33, 0x33, 0x33);


    KeyExprView keyexpr1(keyExpression);
    plist_.erase(plist_.begin(), plist_.end());

     subscriber_ = std::get<Subscriber>(session_->declare_subscriber(keyexpr1,[&] (const Sample *sample)// Capturing object by reference
    { // Capturing object by reference

        //cout<<"Subscriber Lembda triggered. "<<std::endl;
        QPoint tmp;
        plist_.erase(plist_.begin(), plist_.end());

        // Create a dummy when the subscribe button is clicked until the first sample arrives
        
        if(dummy_ == true)
        {
            SharedShape shape;
            if (shape = shape_.lock())
            {
                plist_.push_back(QPoint((IS_WIDTH/2)-10, (IS_HEIGHT/2)-10));
                QBrush brush = QBrush(QColor(0xd3, 0xd3, 0xd3), Qt::SolidPattern);
                shape->setBrush(brush);
                QRect bounds(0, 0, 90, 90);
            }
            
        }

        
        
        if (sample) {

            
            //std::cout << ">> [Subscriber] Received " << " ('"<< sample->get_payload().as_string_view()<<" )'"<<std::endl;

            string_view str_1 = sample->get_payload().as_string_view();
            string text = static_cast<string>(str_1);
            // json reader
            Json::Reader reader;
            // this will contain complete JSON data
            Json::Value completeJsonData;
            // reader reads the data and stores it in completeJsonData
            reader.parse(text, completeJsonData);

            //std::cout<<"color: "<<completeJsonData["color"]<<" x:"<<completeJsonData["x"]<<" y:"<<completeJsonData["y"]<<" shapesize:"<<completeJsonData["shapesize"]<<std::endl;


            dummy_ = false;

            SharedShape shape;
            if (shape = shape_.lock())
            {
                string strColor= completeJsonData["color"].asString();
                //std::cout<<"Color String: "<<strColor<<"  |  Color: "<<color_<<std::endl;
                int _colorIdx_ = convert(strColor);

                sTs.x_ = completeJsonData["x"].asInt64();;
                sTs.y_ = completeJsonData["y"].asInt64();
                sTs.color_ = strColor;
                sTs.ssize_ = completeJsonData["shapesize"].asInt64();
                //std::cout<<"x: "<<sTs.x_<<" , y: "<<sTs.y_<<" , color: "<<sTs.color_<<" , size: "<<sTs.ssize_<<std::endl;
            if (strcmp(strColor.c_str(), color_.c_str()) == 0)
            {              
                tmp.rx() = completeJsonData["x"].asInt64();
                tmp.ry() = completeJsonData["y"].asInt64();
                plist_.push_back(tmp);

                if (attached_ == false)
                {
                    attached_ = true;
                    QBrush brush = QBrush(colorList_[_colorIdx_], Qt::SolidPattern);
                    shape->setBrush(brush);
                }
                QRect bounds(0, 0, completeJsonData["shapesize"].asInt64(), completeJsonData["shapesize"].asInt64());
                shape->setBounds(bounds);
           }
        }

    }
}
)
);
//std::cout<<"subscrited Created"<<std::endl;

}

void ZenohShapeDynamics::setKeyExpression(const std::string& keyExpression)
{
    keyexpr_ = keyExpression;
}

void ZenohShapeDynamics::setSubscriber(const std::string& keyExpression)
{
    //std::cout<<"Key Experssion: "<<keyExpression<<std::endl;
    

    //subscriberList.push_back(std::move(subscriber));
     //subscriber_ = std::move(subscriber);
    //subscriber_ = subscriber;
    //return subscriber;
}


int ZenohShapeDynamics::convert(const std::string& str)
    {
    if(str == "BLUE") return 0;
    else if(str == "RED") return 1;
    else if(str == "GREEN") return 2;
    else if(str == "ORANGE") return 3;
    else if(str == "YELLOW") return 4;
    else if(str == "MAGENTA") return 5;
    else if(str == "CYAN") return 6;
    else if(str == "GRAY") return 7;
    else if(str == "BLACK") return 8;
    }


ZenohShapeDynamics::~ZenohShapeDynamics()
{
}

void
ZenohShapeDynamics::simulate()
{
    //sub_.pull();
    //std::cout<<"Simulation Triggered() "<<std::endl;
    //subscriber_.pull();
    //std::cout<<"x: "<<sTs.x_<<" , y: "<<sTs.y_<<" , color: "<<sTs.color_<<" , size: "<<sTs.ssize_<<std::endl;

}
}}
