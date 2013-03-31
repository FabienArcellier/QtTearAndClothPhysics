#include "canvas.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "physics.h"

Canvas::Canvas() :
    m_physicsAccuracy(3),
    m_mouseInfluence(20),
    m_mouseCut(6),
    m_gravity(900),
    m_clothHeight(30),
    m_clothWidth(50),
    m_startY(20),
    m_spacing(7),
    m_tearDistance(60),
    m_physics(NULL)
{
    this -> m_mouse.down = false;
    this -> m_mouse.button = Qt::LeftButton;
    this -> m_mouse.x = 0;
    this -> m_mouse.y = 0;
    this -> m_mouse.px = 0;
    this -> m_mouse.py = 0;

    this -> setRect(0, 0, this -> m_clothWidth * this -> m_spacing, this -> m_clothHeight * this -> m_spacing);
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
    QRectF rect = this -> rect();
    qreal start_x = rect.width() / 2 - this -> m_clothWidth  * this -> m_spacing / 2;
    for(int y = 0; y < this -> m_clothHeight; y++)
    {
        for(int x = 0; x < this -> m_clothWidth; x++)
        {
            Point* point = this -> CreatePoint(start_x + x * this -> m_spacing,  this -> m_startY + y * this -> m_spacing);

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

void Canvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor strokeStyle(222, 222, 222);
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
    return point;
}

void Canvas::MousePressEvent(QGraphicsSceneMouseEvent *event)
{

    this -> m_mouse.button = event -> button();
    this -> m_mouse.px = this -> m_mouse.x;
    this -> m_mouse.py = this -> m_mouse.y;
    this -> m_mouse.x = event -> lastPos().x();
    this -> m_mouse.y = event -> lastPos().y();
    this -> m_mouse.down = true;
    event -> accept();
}

void Canvas::MouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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
