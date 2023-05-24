#ifndef _ZENOHSHAPEDYNAMICS_HPP
#define _ZENOHSHAPEDYNAMICS_HPP

/** @file */


#include <ShapeDynamics.hpp>
#include <QtCore/QRect>
#include <QtWidgets/QtWidgets>
#include <Shape.hpp>
// -- Shaped Include
//#include "ishape.hpp"
#include "zenoh.hxx"
#include <vector>
#include<queue>
using namespace zenoh;


namespace demo { namespace ishapes {
#define CN 9


 typedef ::std::shared_ptr<Shape> SharedShape; // added
 typedef ::std::weak_ptr<Shape> WeakSharedShape; // added

/**
 * @addtogroup demos_iShapes
 */
/** @{*/

struct ShapeTypeStruct{
    int x_;
    int y_;
    std::string color_;
    int ssize_;
};


class ZenohShapeDynamics : public ShapeDynamics
{
public:
    enum
    {
        BLUE    = 0,
        RED     = 1,
        GREEN   = 2,
        ORANGE  = 3,
        YELLOW  = 4,
        MAGENTA = 5,
        CYAN    = 6,
        GRAY    = 7,
        BLACK   = 8
    };


public:
    ZenohShapeDynamics(
        int x0, int y0,
        std::shared_ptr<Session> session,
        const std::string& keyExpression,
        const std::string& color,
        int colorIdx,
        bool dummy
    );

    int convert(const std::string& str);



    virtual ~ZenohShapeDynamics();

public:
     typedef ::std::shared_ptr<ZenohShapeDynamics> ref_type; // added

public:

    void setShape(SharedShape shape)
    {
        shape_ = shape;
    }

    void setSession(std::shared_ptr<Session> session)
    {
        session_ = std::move(session);
    }

    void setSubscriber(const std::string& keyExpression);
    void setKeyExpression(const std::string& keyExpression);


    virtual void simulate();
    void data_handler(const Sample *sample) ;

private:
    WeakSharedShape shape_;
    int x0_;
    int y0_;
    std::string  keyexpr_;
    bool attached_;
    std::string color_;
    int colorIdx_;
    QColor  colorList_[CN];
    bool updateBounds_;
    bool dummy_;
    std::shared_ptr<Session> session_;
    Subscriber subscriber_;
    ShapeTypeStruct sTs;

};
}
}

/** @}*/

#endif	/* _ZENOHSHAPEDYNAMICS_HPP */
