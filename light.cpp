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


void light::countTangents(Vertex* Vertices)
{
    for (unsigned int i = 0 ; i < 36 ; i += 3) {
        Vertex& v0 = Vertices[i];
        Vertex& v1 = Vertices[i+1];
        Vertex& v2 = Vertices[i+2];

        QVector3D Edge1 = v1.position() - v0.position();
        QVector3D Edge2 = v2.position() - v0.position();

        float DeltaU1 = v1.texCoord().x() - v0.texCoord().x();
        float DeltaV1 = v1.texCoord().y() - v0.texCoord().y();
        float DeltaU2 = v2.texCoord().x() - v0.texCoord().x();
        float DeltaV2 = v2.texCoord().y() - v0.texCoord().y();

        float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

        QVector3D Tangent, Bitangent;

        Tangent.setX(f * (DeltaV2 * Edge1.x() - DeltaV1 * Edge2.x()));
        Tangent.setY(f * (DeltaV2 * Edge1.y() - DeltaV1 * Edge2.y()));
        Tangent.setZ(f * (DeltaV2 * Edge1.z() - DeltaV1 * Edge2.z()));

        Bitangent.setX(f * (-DeltaU2 * Edge1.x() - DeltaU1 * Edge2.x()));
        Bitangent.setY(f * (-DeltaU2 * Edge1.y() - DeltaU1 * Edge2.y()));
        Bitangent.setZ(f * (-DeltaU2 * Edge1.z() - DeltaU1 * Edge2.z()));

        v0.addTangent(Tangent);
        v1.addTangent(Tangent);
        v2.addTangent(Tangent);
    }

    for (unsigned int i = 0 ; i < 36 ; i++) {
        Vertices[i].normalizeTangent();
    }
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
