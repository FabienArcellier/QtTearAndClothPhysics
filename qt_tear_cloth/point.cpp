#include "point.h"

#include <QPainter>
#include "constraint.h"

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
    m_pinY(0)
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
