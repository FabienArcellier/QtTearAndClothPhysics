#include "constraint.h"

#include <qmath.h>
#include <QPainter>

#include "point.h"


Constraint::Constraint(Point *p1, Point *p2, qreal length, qreal tear_distance, QObject *parent) :
    QObject(parent),
    m_p1(p1),
    m_p2(p2),
    m_length(length),
    m_tearDistance(tear_distance)
{
    Q_CHECK_PTR(this -> m_p1);
    Q_CHECK_PTR(this -> m_p2);
    Q_ASSERT(length >= 0);
    Q_ASSERT(tear_distance >= 0);
}

void Constraint::Solve()
{
    qreal diff_x = this -> m_p1 -> x() - this -> m_p2 -> x();
    qreal diff_y = this -> m_p1 -> y() - this -> m_p2 -> y();
    qreal distance = qSqrt(diff_x * diff_x + diff_y * diff_y);
    qreal diff_distance = (this -> m_length - distance)/distance;

    if (diff_distance > this -> m_tearDistance)
    {
        this -> m_p1 -> RemoveConstraint(this);
    }

    // scalar_1 is the ratio from p1 mass in comparaison with the p1 mass + p2 mass
    qreal scalar_1 = ((1 / this -> m_p1 -> mass()) / (1 / this -> m_p1 -> mass() + 1 / this -> m_p2 -> mass()));
    qreal scalar_2 = 1 - scalar_1;

    // Find a way to use directly arithmetic operation
    qreal x1_new = this -> m_p1 -> x() + diff_x * scalar_1 * diff_distance;
    this -> m_p1 -> setX(x1_new);
    qreal y1_new = this -> m_p1 -> y() + diff_y * scalar_1 * diff_distance;
    this -> m_p1 -> setY(y1_new);

    qreal x2_new = this -> m_p2 -> x() - diff_x * scalar_2 * diff_distance;
    this -> m_p2 -> setX(x2_new);
    qreal y2_new = this -> m_p2 -> y() - diff_y * scalar_2 * diff_distance;
    this -> m_p2 -> setY(y2_new);
}

void Constraint::Draw(QPainter *painter)
{
    QPointF point1(this -> m_p1 -> x(), this -> m_p1 -> y());
    QPointF point2(this -> m_p2 -> x(), this -> m_p2 -> y());
    painter -> drawLine(point1, point2);
}
