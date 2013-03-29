#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <QObject>

class Point;

class Constraint : public QObject
{
    Q_OBJECT
public:
    explicit Constraint(Point* p1, Point* p2, qreal length, qreal tear_distance, QObject *parent = 0);
    void Solve();
    
private:
    Point* m_p1;
    Point* m_p2;
    qreal m_length;
    qreal m_tearDistance;
};

#endif // CONSTRAINT_H
