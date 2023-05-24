/**
 * @file
 */
#include "BouncingShapeDynamics.hpp"
#include <math.h>
#include <stdlib.h>

#include <iostream>
static const float PI = 3.1415926535F;
#ifdef TESTBUILD
    #include <QtCore/QDebug>
    #include "os_time.h"
#endif
#ifdef WIN32
#define roundf(a) ((a)>0?floor((a)+0.5):ceil((a)-0.5))
#endif

namespace demo { namespace ishapes {

BouncingShapeDynamics::BouncingShapeDynamics(int x0, int y0,
        const QRect& shapeBounds,
        const QRect& constraint,
        float angle,
        float speed,
        const ShapeType& shape,
        Publisher pub)
    :   ShapeDynamics(x0, y0, constraint),
        shapeBounds_(shapeBounds),
        alpha_(angle),
        angle_(angle),
        speed_(speed),
        shape_(shape),
        pub_(std::move(pub))
{ }


BouncingShapeDynamics::~BouncingShapeDynamics()
{ 
    //pub_.delete_resource();
}

bool
BouncingShapeDynamics::flip()
{
    bool doflip = false;
    if (rand() <= RAND_MAX/2)
        doflip = true;

    return doflip;
}

void
BouncingShapeDynamics::simulate()
{
    pos_.rx() = roundf(pos_.rx() + speed_*cosf(angle_));
    pos_.ry() = roundf(pos_.ry() + speed_*sinf(angle_));

    if (pos_.x() <= 0)
    {
        angle_ = this->flip() ? -alpha_ : alpha_;
        pos_.rx() = 0;
    }
    else if (pos_.x() >= (constraint_.width() - (shapeBounds_.width())))
    {
        angle_ = this->flip() ? (PI + alpha_) : (PI - alpha_);
        pos_.rx() = constraint_.width() - shapeBounds_.width();
    }
    else if (pos_.y() <= 0)
    {
        angle_ = this->flip() ? alpha_ : PI - alpha_;
        pos_.ry() = 0;
    }
    else if (pos_.y() >= (constraint_.height() - shapeBounds_.height()))
    {
        angle_ = this->flip() ? (PI+alpha_) : -alpha_;
        pos_.ry() = constraint_.height() - shapeBounds_.height();
    }

    shape_.x() = pos_.x();
    shape_.y() = pos_.y();

    std::string msg = "{ \"color\" : \""+shape_.color()+"\", \"x\" : "+std::to_string(shape_.x())+", \"y\" : "+std::to_string(shape_.y())+", \"shapesize\" : "+ std::to_string(shape_.shapesize())+" }";
    //std::cout<<msg<<std::endl;
    pub_.put(msg);


    plist_.erase(plist_.begin(), plist_.end());
    plist_.push_back(pos_);
    #ifdef TESTBUILD
        qDebug() << "Time:"
                 << os_timeGet().tv_sec
                 << os_timeGet().tv_nsec
                 << "Colour:"
                 << shape_.color().c_str()
                 << "Size:" << shape_.shapesize()
                 << "x:" << shape_.x()
                 << "y:" << shape_.y();
    #endif
}
}}
