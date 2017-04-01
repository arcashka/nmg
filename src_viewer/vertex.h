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

    const QVector3D& getPosition()          { return this->position; }
    void setPosition(QVector3D& position)   { this->position = position; }

private:
    QVector3D position;
};

#endif // VERTEX_H
