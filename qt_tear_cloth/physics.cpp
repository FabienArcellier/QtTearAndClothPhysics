#include "physics.h"

#include "point.h"

Physics::Physics(qint32 physics_accuracy, QObject *parent) :
    QObject(parent),
    m_physicsAccuracy(physics_accuracy),
    m_deltaSec((qreal)16 / (qreal)1000),
    m_points(NULL)

{
    Q_ASSERT(physics_accuracy >= 0);
}

qreal Physics::DeltaSec() const
{
    return this -> m_deltaSec;
}

qint32 Physics::PhysicsAccuracy() const
{
    return this -> m_physicsAccuracy;
}

void Physics::SetPhysicsAccuracy(qint32 physics_accuracy)
{
    Q_ASSERT(physics_accuracy >= 0);
    this -> m_physicsAccuracy = physics_accuracy;
}

void Physics::SetPoints(QList<Point*> *points)
{
    this -> m_points = points;
}

void Physics::Update()
{
    qint32 i = this -> m_physicsAccuracy;
    while(i--)
    {
        for(int j = 0; j < this -> m_points -> count(); j++)
        {
            this -> m_points -> at(j) -> SolveConstraints();
        }
    }

    i = this -> m_points -> count();
    while(i--)
    {
        this -> m_points -> at(i) -> UpdateMouse();
        this -> m_points -> at(i) -> Update(this -> m_deltaSec);
    }
}
