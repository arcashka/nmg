#include "camera.h"
#include <QQuaternion>
Camera::Camera()
{

}

void Camera::translateBy(QVector3D a)
{
    dirty = true;
    eye += a;
}

void Camera::rotateCenter(float angle)
{
    dirty = true;
    center = QQuaternion(angle, QVector3D(0.0f, 0.0f, 1.0f)) * center;
}

void Camera::rotateUp(float angle)
{
    dirty = true;
    up = QQuaternion(angle, QVector3D(1.0f, 0.0f, 0.0f)) * up;
}
