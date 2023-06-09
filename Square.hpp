#ifndef _SQUARE_HPP
#define _SQUARE_HPP

/** @file */
/**
 * @addtogroup demos_iShapes
 */
/** @{*/

#include <QtWidgets/QtWidgets>
#include <Shape.hpp>
#include <ShapeDynamics.hpp>

namespace demo { namespace ishapes {
class Square : public Shape
{
public:
    Square(const QRect& bounds,
           ShapeDynamics::ref_type dynamics,
           const QPen& pen,
           const QBrush& brush,
           bool targeted = false);

    virtual ~Square();

public:
typedef ::std::shared_ptr<ShapeDynamics> SharedShapeDynamics; // added

public:
    virtual void update();
    virtual void paint(QPainter& painter);
private:
    Square(const Square& orig);
    Square& operator=(const Square&);

private:
     ShapeDynamics::ref_type dynamics_;

};
}
}

/** @}*/

#endif	/* _SQUARE_HPP */
