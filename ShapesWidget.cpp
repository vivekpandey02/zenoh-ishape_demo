/**
 * @file
 */
#include <iostream>
#include <QtWidgets/QtWidgets>
#include "ShapesWidget.hpp"
#include "config.hpp"


#define LOGO ":/images/zenoh-br.png"


namespace demo { namespace ishapes {


ShapesWidget::ShapesWidget(QWidget *parent)
    : QWidget(parent),
      showCurrentFilter_(false),
      logo_(LOGO),
      paused_(false)
{
    this->setBackgroundRole(QPalette::Base);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

ShapesWidget::~ShapesWidget()
{
}

void
ShapesWidget::addShape(Shape::ref_type shape)
{
    shapeList_.push_back(shape);
    //std::cout<<"shape added. "<<std::endl;
}

void
ShapesWidget::nextAnimationFrame()
{
    if(!this->paused())
    {
        this->update();

        ShapeList::iterator index = shapeList_.begin();
        while (index != shapeList_.end())
        {
            (*index)->update();
            ++index;
        }
    }
}

void
ShapesWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(ISOCPP_LOGO_X, ISOCPP_LOGO_Y, logo_);
    if (showCurrentFilter_)
    {
        QBrush brush(QColor(0x99,0x99,0x99,0x99), Qt::SolidPattern);
        painter.setBrush(brush);
        painter.drawRect(currentFilter_);
    }
    ShapeList::iterator index = shapeList_.begin();
    while (index != shapeList_.end())
    {
        (*index)->paint(painter);
        ++index;
    }
    painter.end();
}

void
ShapesWidget::addFilter(const QRect& filter)
{
    filterList_.push_back(filter);
}

void ShapesWidget::displayFilter(const QRect& currentFilter)
{
    currentFilter_ = currentFilter;
    showCurrentFilter_ = true;
    this->update();
}
}}
