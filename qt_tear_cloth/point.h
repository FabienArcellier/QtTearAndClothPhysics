#ifndef POINT_H
#define POINT_H

#include <QObject>

class QPainter;
class Constraint;
class Mouse;

class Point : public QObject
{
    Q_OBJECT
public:
    explicit Point(qreal x, qreal y, QObject* parent = 0);
    ~Point();

    void Attach(Point*, qreal spacing, qreal tear_length);
    void ClearConstraint();
    void RemoveConstraint(Constraint*);
    void Pin(qreal p_x, qreal p_y);
    void SolveConstraints();
    void UpdateMouse();
    void Update(qreal delta);
    void Draw(QPainter* painter);
    void SetMouse(Mouse* mouse);
    void SetMouseInfluence(qint32 mouse_influence);
    void SetGravity(qreal);
    void AddForce(qreal fX, qreal fY);

    qreal x() const
    {
        return this -> m_x;
    }

    void setX(const qreal x)
    {
        this -> m_x = x;
    }

    qreal y() const
    {
        return this -> m_y;
    }

    void setY(const qreal y)
    {
        this -> m_y = y;
    }

    qreal mass() const
    {
        return this -> m_mass;
    }

    void SetMouseCut(qint32 value)
    {
        this -> m_mouseCut = value;
    }

private:
    qreal m_x;
    qreal m_y;
    qreal m_px;
    qreal m_py;
    qreal m_ax;
    qreal m_ay;
    qreal m_mass;
    QList<Constraint* > m_constraints;
    bool m_pinned;
    qreal m_pinX;
    qreal m_pinY;
    Mouse* m_mouse;
    qint32 m_mouseInfluence;
    qreal m_gravity;
    qint32 m_mouseCut;
};

#endif // POINT_H
