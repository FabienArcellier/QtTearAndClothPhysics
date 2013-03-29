#ifndef POINT_H
#define POINT_H

#include <QObject>

class Constraint;

class Point : public QObject
{
    Q_OBJECT
public:
    explicit Point(qreal x, qreal y, QObject* parent = 0);
    ~Point();

private:
    qreal m_x;
    qreal m_y;
    qreal m_px;
    qreal m_py;
    qreal m_ax;
    qreal m_ay;
    qreal m_mass;
    QList<Constraint* > m_contraints;
    bool m_pinned;
    qreal m_pinX;
    qreal m_pinY;
};

#endif // POINT_H
