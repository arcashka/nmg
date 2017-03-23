#include "light.h"

light::light()
{
    rotator = QQuaternion();
    light::m_AmbientIntensity = 0.5f;
    light::m_color = QVector3D(1.0f, 1.0f, 1.0f);
    light::m_DiffuseIntensity = 0.8f;
    light::m_Direction = QVector3D(0.0f, 0.0f, -1.0f);
    light::m_SpecularPower = 100.0f;
}


void light::rotateLeft()
{
    rotate(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 5.0f));
    world.setToIdentity();
    world.rotate(rotator.inverted());
    m_Direction = world * m_Direction;

}

void light::rotateDown()
{
    rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 5.0f));
    world.setToIdentity();
    world.rotate(rotator);
    m_Direction = world * m_Direction;
}

void light::rotateUp()
{
    rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 5.0f));
    world.setToIdentity();
    world.rotate(rotator.inverted());
    m_Direction = world * m_Direction;
}

void light::rotateRight()
{
    rotate(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 5.0f));
    world.setToIdentity();
    world.rotate(rotator);
    m_Direction = world * m_Direction;
}
