#include "light.h"

Light::Light()
{
    rotator = QQuaternion();
    Light::m_AmbientIntensity = 0.5f;
    Light::m_color = QVector3D(1.0f, 1.0f, 1.0f);
    Light::m_DiffuseIntensity = 0.8f;
    Light::m_Direction = QVector3D(0.0f, 0.0f, -1.0f);
    Light::m_SpecularPower = 100.0f;
}


void Light::rotateLeft()
{
    rotate(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 5.0f));
    world.setToIdentity();
    world.rotate(rotator.inverted());
    m_Direction = world * m_Direction;
}

void Light::rotateDown()
{
    rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 5.0f));
    world.setToIdentity();
    world.rotate(rotator);
    m_Direction = world * m_Direction;
}

void Light::rotateUp()
{
    rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 5.0f));
    world.setToIdentity();
    world.rotate(rotator.inverted());
    m_Direction = world * m_Direction;
}

void Light::rotateRight()
{
    rotate(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 5.0f));
    world.setToIdentity();
    world.rotate(rotator);
    m_Direction = world * m_Direction;
}
