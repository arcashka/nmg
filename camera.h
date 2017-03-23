#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();
    Camera(QVector3D& eye, QVector3D& center, QVector3D& up) {
        this->eye = eye; this->center = center; this->up = up;
    }

    QVector3D& getEye()     { return eye; }
    QVector3D& getCenter()  { return center; }
    QVector3D& getUp()      { return up; }

    void translateBy(QVector3D a);
    void rotateCenter(float angle);
    void rotateUp(float angle);
private:
    bool dirty;
    QVector3D eye;
    QVector3D center;
    QVector3D up;
};

#endif // CAMERA_H
