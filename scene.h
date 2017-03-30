#ifndef SCENE_H
#define SCENE_H
#include <QQuaternion>
#include <QMatrix4x4>
#include <QImage>
#include <QVector3D>
#include "camera.h"
#include "transform.h"
#include "vertex.h"
#include "light.h"

class Scene
{
public:
    Scene();

    // camera
    void setCameraTranslation(const QVector3D &translation);
    void setCameraRotation(float xRot, const QVector3D axis);

    void translateCameraBy(float speed, const QVector3D axis);
    // right handed
    // relative to rotations
    QVector3D forwardCamera() const         { return camera.forward(); }
    QVector3D upCamera() const              { return camera.up(); }
    QVector3D rightCamera() const           { return camera.right(); }
    // local
    QVector3D forwardLocalCamera() const    { return camera.localForward(); }
    QVector3D upLocalCamera() const         { return camera.localUp(); }
    QVector3D rightLocalCamera() const      { return camera.localRight(); }


    // transform
    void setTransformTranslation(const QVector3D &translation);
    void setTransformScale(float scale);
    void setTransformRotation(float xRot, float yRot);
    // left handed
    // relative to rotations
    QVector3D forwardTransform() const      { return transform.forward(); }
    QVector3D upTransform() const           { return transform.up(); }
    QVector3D rightTransform() const        { return transform.right(); }

    void changeProjection(int width, int height);

    const QMatrix4x4 &getModelToWorldMatrix();
    const QMatrix4x4 &getWorldToCameraMatrix();
    const QMatrix4x4 &getCameraToViewMatrix();
private:
    Camera camera;
    Transform transform;
    QMatrix4x4 projection;
    Light light;
};


static const Vertex vertices[] {
    // front
    Vertex( 0.5f,  0.5f,  0.5f),
    Vertex(-0.5f,  0.5f,  0.5f),
    Vertex(-0.5f,  -0.5f,  0.5f),
    Vertex(-0.5f,  -0.5f,  0.5f),
    Vertex(0.5f,  -0.5f,  0.5f),
    Vertex( 0.5f,  0.5f,  0.5f),
    // back
    Vertex(-0.5f,  0.5f,  -0.5f),
    Vertex(0.5f,  0.5f,  -0.5f),
    Vertex(0.5f,  -0.5f,  -0.5f),
    Vertex(0.5f,  -0.5f,  -0.5f),
    Vertex(-0.5f,  -0.5f,  -0.5f),
    Vertex(-0.5f,  0.5f,  -0.5f),
    // top
    Vertex(0.5f, 0.5f,  -0.5f),
    Vertex(-0.5f, 0.5f,  -0.5f),
    Vertex(-0.5f, 0.5f,  0.5f),
    Vertex(-0.5f, 0.5f,  0.5f),
    Vertex(0.5f, 0.5f,  0.5f),
    Vertex(0.5f, 0.5f,  -0.5f),
    // bot
    Vertex(-0.5f,  -0.5f,  -0.5f),
    Vertex(0.5f,  -0.5f,  -0.5f),
    Vertex(0.5f,  -0.5f,  0.5f),
    Vertex(0.5f,  -0.5f,  0.5f),
    Vertex(-0.5f,  -0.5f,  0.5f),
    Vertex(-0.5f,  -0.5f,  -0.5f),
    // left
    Vertex(-0.5f,  0.5f,  0.5f),
    Vertex(-0.5f,  0.5f,  -0.5f),
    Vertex(-0.5f,  -0.5f,  -0.5f),
    Vertex(-0.5f,  -0.5f,  -0.5f),
    Vertex(-0.5f,  -0.5f,  0.5f),
    Vertex(-0.5f,  0.5f,  0.5f),
    // righ
    Vertex(0.5f,  0.5f,  -0.5f),
    Vertex(0.5f,  0.5f,  0.5f),
    Vertex(0.5f,  -0.5f,  0.5f),
    Vertex(0.5f,  -0.5f,  0.5f),
    Vertex(0.5f,  -0.5f,  -0.5f),
    Vertex(0.5f,  0.5f,  -0.5f)
};


#endif // SCENE_H
