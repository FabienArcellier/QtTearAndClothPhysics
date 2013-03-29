#ifndef CANVAS_H
#define CANVAS_H

#include <QList>
#include <QGraphicsRectItem>
#include "mainwindow.h"
#include "point.h"

class Canvas : public QGraphicsRectItem
{
public:
    Canvas(Mouse* m_mouse);
    ~Canvas();

protected:
    void MousePressEvent(QGraphicsSceneMouseEvent *event);
    void MouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect();
    void createPoint(int x, int y);

private:
    Mouse* m_mouse;
    QList<Point*> m_points;
};

#endif // CANVAS_H
