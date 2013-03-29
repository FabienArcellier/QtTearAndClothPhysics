#include "canvas.h"

#include <QGraphicsSceneMouseEvent>

Canvas::Canvas(MainWindow *parent)
{
    this -> m_parent = parent;
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    mouse -> button = (qint32) event -> button();
    mouse -> px = mouse -> x;
    mouse -> py = mouse -> y;
    mouse -> x = event -> lastPos().x();
    mouse -> y = event -> lastPos().y();
    mouse -> down = true;
    event -> accept();
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Mouse* mouse = this -> m_parent -> mouse();
    mouse -> down = false;
    event -> accept();
}
