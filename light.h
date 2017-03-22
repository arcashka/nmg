#ifndef LIGHT_H
#define LIGHT_H
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include "vertex.h"

class light
{
private:
    QVector3D m_color;
    float m_AmbientIntensity;
    QVector3D m_Direction;
    float m_DiffuseIntensity;
    float m_SpecularPower;

    QMatrix4x4 world;
    QQuaternion rotator;
public:
    // mutators
    void inline setColor(const QVector3D& color) { m_color = color; }
    void inline setAmbientIntensity(const float& ambInt) { m_AmbientIntensity = ambInt; }
    void inline setDirection(const QVector3D& direction) { m_Direction = direction; }
    void inline setDiffuseIntensity(const float& difInt) { m_DiffuseIntensity = difInt; }
    void inline setSpecularPower(const float& specPower) { m_SpecularPower = specPower; }

    // accessors
    inline const QVector3D& Color() { return m_color; }
    inline const float& AmbientIntensity() { return m_AmbientIntensity; }
    inline const QVector3D& Direction() { return m_Direction; }
    inline const float& DiffuseIntensity() { return m_DiffuseIntensity; }
    inline const float& SpecularPower() { return m_SpecularPower; }
    light();

    void inline rotate(const QQuaternion &dr) { rotator = dr; }
    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();

    void countTangents(Vertex* Vertices);
};

#endif // LIGHT_H
