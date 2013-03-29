#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsRectItem>
#include "mainwindow.h"

class Canvas : public QGraphicsRectItem
{
public:
    Canvas(MainWindow* parent);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    MainWindow* m_parent;
};

#endif // CANVAS_H
