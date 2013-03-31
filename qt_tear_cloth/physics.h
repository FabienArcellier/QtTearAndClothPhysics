#ifndef PHYSICS_H
#define PHYSICS_H

#include <QList>
#include <QObject>
class Point;

class Physics : public QObject
{
    Q_OBJECT
public:
    explicit Physics(qint32 physics_accuracy, QObject *parent = 0);

    qreal DeltaSec() const;
    qint32 PhysicsAccuracy() const;
    void SetPhysicsAccuracy(qint32 physics_accuracy);
    void SetPoints(QList<Point*> *);

    void Update();
    
private:
    qint32 m_physicsAccuracy;
    qreal m_deltaSec;
    QList<Point*> * m_points;
    
};

#endif // PHYSICS_H
