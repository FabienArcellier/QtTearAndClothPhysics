#include "canvas.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

Canvas::Canvas(Mouse *mouse)
{
    this -> m_mouse = mouse;
}

Canvas::~Canvas()
{
    for(int i = 0; i < this -> m_points.count(); i++)
    {
        Point* point_to_delete = this -> m_points[0];
        this -> m_points.removeAt(0);
        delete point_to_delete;
    }
}

void Canvas::MousePressEvent(QGraphicsSceneMouseEvent *event)
{

    this -> m_mouse -> button = (qint32) event -> button();
    this -> m_mouse -> px = this -> m_mouse -> x;
    this -> m_mouse -> py = this -> m_mouse -> y;
    this -> m_mouse -> x = event -> lastPos().x();
    this -> m_mouse -> y = event -> lastPos().y();
    this -> m_mouse -> down = true;
    event -> accept();
}

void Canvas::MouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this -> m_mouse -> down = false;
    event -> accept();
}

void Canvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter -> setPen(Qt::black);
    painter -> drawRect(this -> rect());
}

QRectF Canvas::boundingRect()
{
    return rect();
}

void Canvas::createPoint(int x, int y)
{

}

