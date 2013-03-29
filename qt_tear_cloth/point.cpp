#include "point.h"

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
    for(int i = 0; i < this -> m_contraints.count(); i++)
    {
        Constraint* constraint_to_delete = this -> m_contraints.first();
        this -> m_contraints.removeAt(0);
        delete constraint_to_delete;
    }
}
