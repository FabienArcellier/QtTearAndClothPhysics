#include "canvas.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "physics.h"

Canvas::Canvas() :
    m_physicsAccuracy(3),
    m_mouseInfluence(20),
    m_mouseCut(6),
    m_gravity(900),
    m_clothHeight(50),
    m_clothWidth(100),
    m_startY(20),
    m_spacing(7),
    m_tearDistance(100),
    m_physics(NULL)
{
    this -> m_mouse.down = false;
    this -> m_mouse.button = Qt::LeftButton;
    this -> m_mouse.x = 0;
    this -> m_mouse.y = 0;
    this -> m_mouse.px = 0;
    this -> m_mouse.py = 0;

    this -> setAcceptHoverEvents(true);
    this -> setRect(0, 0, (this -> m_clothWidth * 2) * this -> m_spacing, (this -> m_clothHeight * 2) * this -> m_spacing);
    this -> Init();
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

void Canvas::BuildCloth()
{
    qreal start_x = 5;
    for(int y = 0; y < this -> m_clothHeight; y++)
    {
        for(int x = 0; x < this -> m_clothWidth; x++)
        {
            Point* point = this -> CreatePoint(start_x + x * this -> m_spacing,  y);

            if (x != 0)
            {
                point->Attach(m_points.at(m_points.length() - 1), this -> m_spacing, this -> m_tearDistance);
            }

            if (y != 0)
            {
                point->Attach(m_points.at((y - 1) * (this -> m_clothWidth) + x), this -> m_spacing, this -> m_tearDistance);
            }

            if (y == 0)
            {
                point->Pin(point -> x(), point -> y());
            }

            m_points.append(point);
        }
    }
}


void Canvas::Update()
{
    this -> m_physics -> Update();
    this -> update(this -> rect());
}

void Canvas::ResetSimulation()
{
    foreach(Point* point, this -> m_points)
    {
        this -> m_points.removeFirst();
        delete point;
    }

    this -> BuildCloth();
    this -> Update();
}

void Canvas::SetPhysicsAccuracy(qint32 value)
{
    this -> m_physicsAccuracy = value;
    this -> m_physics -> SetPhysicsAccuracy(value);
}

void Canvas::SetMouseInfluence(qint32 value)
{
    this -> m_mouseInfluence = value;
    foreach(Point* point, this -> m_points)
    {
        point -> SetMouseInfluence(value);
    }
}

void Canvas::SetMouseCut(qint32 value)
{
    this -> m_mouseCut = value;
    foreach(Point* point, this -> m_points)
    {
        point -> SetMouseCut(value);
    }
}

void Canvas::SetGravity(qint32 value)
{
    this -> m_gravity = value;
    foreach(Point* point, this -> m_points)
    {
        point -> SetGravity(value);
    }
}

void Canvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor strokeStyle(0, 0, 0);
    painter -> setPen(strokeStyle);
    for(int i = 0; i < this -> m_points.count(); i++)
    {
        this -> m_points.at(i) -> Draw(painter);
    }
}

QRectF Canvas::boundingRect()
{
    return this -> rect();
}

Point* Canvas::CreatePoint(qreal x, qreal y)
{
    Point* point = new Point(x, y);
    point -> SetMouse(&(this -> m_mouse));
    point -> SetMouseInfluence(this -> m_mouseInfluence);
    point -> SetMouseCut(this -> m_mouseCut);
    point -> SetGravity(this -> m_gravity);
    return point;
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    this -> m_mouse.button = event -> button();
    this -> m_mouse.px = this -> m_mouse.x;
    this -> m_mouse.py = this -> m_mouse.y;
    this -> m_mouse.x = event -> lastPos().x();
    this -> m_mouse.y = event -> lastPos().y();
    this -> m_mouse.down = true;
    event -> accept();
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this -> m_mouse.px = this -> m_mouse.x;
    this -> m_mouse.py = this -> m_mouse.y;
    this -> m_mouse.x = event -> lastPos().x();
    this -> m_mouse.y = event -> lastPos().y();
    event -> accept();
}

void Canvas::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (event -> lastPos().x() != this -> m_mouse.x &&
            event -> lastPos().y() != this -> m_mouse.y)
    {
        this -> m_mouse.px = this -> m_mouse.x;
        this -> m_mouse.py = this -> m_mouse.y;
        this -> m_mouse.x = event -> lastPos().x();
        this -> m_mouse.y = event -> lastPos().y();
        event -> accept();
    }
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this -> m_mouse.down = false;
    event -> accept();
}

void Canvas::Init()
{
    this -> m_physics = new Physics(this -> m_physicsAccuracy);
    this -> m_physics -> SetPoints(&(this -> m_points));

    this -> BuildCloth();
    this -> Update();
}
