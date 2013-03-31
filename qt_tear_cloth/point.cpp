#include "point.h"

#include <qmath.h>
#include <QPainter>
#include <QDebug>
#include "constraint.h"

// I have to manage dependance with Mouse
// differently.
#include "canvas.h"

Point::Point(qreal x, qreal y, QObject *parent) :
    QObject(parent),
    m_x(x),
    m_y(y),
    m_px(x),
    m_py(y),
    m_ax(0),
    m_ay(0),
    m_mass(1),
    m_pinned(false),
    m_pinX(0),
    m_pinY(0),
    m_mouse(NULL),
    m_mouseInfluence(0)
{
}

Point::~Point()
{
    for(int i = 0; i < this -> m_constraints.count(); i++)
    {
        Constraint* constraint_to_delete = this -> m_constraints.first();
        this -> m_constraints.removeAt(0);
        delete constraint_to_delete;
    }
}

void Point::Attach(Point *p2, qreal spacing, qreal tear_length)
{
    Constraint* constraint = new Constraint(this, p2, spacing, tear_length);
    this -> m_constraints.append(constraint);
}

void Point::RemoveConstraint(Constraint* constraint)
{
    this -> m_constraints.removeOne(constraint);
    delete constraint;
}

void Point::Pin(qreal px, qreal py)
{
    this -> m_pinned = true;
    this -> m_px = px;
    this -> m_py = py;
}

void Point::SolveConstraints()
{

}

void Point::UpdateMouse()
{
    Q_CHECK_PTR(this -> m_mouse);
    if (this -> m_mouse -> down == false)
    {
        return;
    }

    qreal diff_x = this -> x() - this -> m_mouse -> x;
    qreal diff_y = this -> y() - this -> m_mouse -> y;
    qreal distance = qSqrt(diff_x * diff_x + diff_y * diff_y);
    if (this -> m_mouse -> button == Qt::LeftButton)
    {
        if (distance < this -> m_mouseInfluence)
        {
            // Why 1.8 ?
            this -> m_px = this -> m_x - (this -> m_mouse -> x - this -> m_mouse->px) * 1.8;
            this -> m_py = this -> m_y - (this -> m_mouse -> y - this -> m_mouse->py) * 1.8;
            qDebug() << "Point change catched x:" << this -> m_px << " y:" <<  this -> m_py ;
        }
    }
}

void Point::Update(qreal delta)
{

}

void Point::Draw(QPainter* painter)
{
    if (this -> m_constraints.count() == 0)
    {
        return;
    }

    foreach(Constraint* constraint, this -> m_constraints)
    {
        constraint -> Draw(painter);
    }
}

void Point::SetMouse(Mouse* mouse)
{
    this -> m_mouse = mouse;
}

void Point::SetMouseInfluence(qint32 mouse_influence)
{
    this -> m_mouseInfluence = mouse_influence;
}
