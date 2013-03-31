#ifndef CANVAS_H
#define CANVAS_H

#include <QList>
#include <QGraphicsRectItem>
#include "point.h"

class Mouse
{
public:
    bool down;
    Qt::MouseButton button;
    qint32 x;
    qint32 y;
    qint32 px;
    qint32 py;
};

class Physics;

class Canvas : public QGraphicsRectItem
{
public:
    Canvas();
    ~Canvas();
    Point *CreatePoint(qreal x, qreal y);
    void BuildCloth();
    void Update();

protected:
    void MousePressEvent(QGraphicsSceneMouseEvent *event);
    void MouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect();

private:
    void Init();
    QList<Point*> m_points;
    Mouse m_mouse;
    qint32 m_physicsAccuracy;
    qint32 m_mouseInfluence;
    qint32 m_mouseCut;
    qint32 m_gravity;
    qint32 m_clothHeight;
    qint32 m_clothWidth;
    qint32 m_startY;
    qint32 m_spacing;
    qint32 m_tearDistance;
    Physics* m_physics;
};

#endif // CANVAS_H
