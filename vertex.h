#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>

class Vertex
{
public:
    // Constructors
    Vertex();
    Vertex(const QVector3D &position);

    const QVector3D& getPosition()          { return this->position; }
    void setPosition(QVector3D& position)   { this->position = position; }

private:
    QVector3D position;
};

Vertex::Vertex(const QVector3D &position) {
    this->position = position;
}

#endif // VERTEX_H
