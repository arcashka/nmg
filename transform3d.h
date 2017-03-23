#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include <QDebug>

class Transform3D
{
public:
    Transform3D();
    const QMatrix4x4& toMatrix();
private:
    bool dirty;
    QVector3D translation;
    QVector3D scale;
    QQuaternion rotation;
    QMatrix4x4 world;
};


#endif // TRANSFORM3D_H
