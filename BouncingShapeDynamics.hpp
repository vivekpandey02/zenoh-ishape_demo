#ifndef _BOUNCINGSHAPEDYNAMICS_HPP
#define _BOUNCINGSHAPEDYNAMICS_HPP

/** @file */
/**
 * @addtogroup demos_iShapes
 */
/** @{*/


#include <ShapeDynamics.hpp>
#include <QtCore/QRect>

// -- Shaped Include
#include "ishape.hpp"
#include "zenoh.hxx"
using namespace zenoh;
#pragma once


namespace demo { namespace ishapes {
class BouncingShapeDynamics : public ShapeDynamics   
{
public:
    BouncingShapeDynamics(int x0, int y0,
                          const QRect& shapeBounds,
                          const QRect& constraints,
                          float speed,
                          float angle,
                          const ShapeType& shape,
                          Publisher pub);

    virtual ~BouncingShapeDynamics();

public:
    virtual void simulate();

public:
    typedef ::std::shared_ptr<BouncingShapeDynamics> ref_type; // added

private:
    BouncingShapeDynamics(const BouncingShapeDynamics& orig);
    BouncingShapeDynamics& operator=(const BouncingShapeDynamics&);

private:
    bool flip();

private:
    QRect shapeBounds_;
    float alpha_;
    float angle_;
    float speed_;
    ShapeType shape_;
    Publisher pub_;
};
}
}

/** @}*/

#endif	/* _BOUNCINGSHAPEDYNAMICS_HPP */
