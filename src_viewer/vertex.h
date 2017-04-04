#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex
{
public:
    // Constructors
    Vertex();
    Vertex(const QVector3D &position) { this->position = position; }
    Vertex(float x, float y, float z) { position = QVector3D(x, y, z); }
    Vertex(float x, float y, float z, float xx, float yy, float zz) { position = QVector3D(x, y, z); normal = QVector3D(xx, yy, zz); }

    const QVector3D& getPosition()          { return this->position; }
    void setPosition(QVector3D& position)   { this->position = position; }
    static int positionOfsset() { return offsetof(Vertex, position); }
    static int normalOffset()      { return offsetof(Vertex, normal); }
    static int stride() { return sizeof(Vertex); }
private:
    QVector3D position;
    QVector3D normal;
};

#endif // VERTEX_H
