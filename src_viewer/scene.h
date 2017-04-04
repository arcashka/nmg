#ifndef SCENE_H
#define SCENE_H
#include <QQuaternion>
#include <QMatrix4x4>
#include <QImage>
#include <QVector3D>
#include <QOpenGLTexture>
#include <QImage>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QImage>

#include "src_viewer/camera.h"
#include "src_viewer/transform.h"
#include "src_viewer/vertex.h"
#include "src_viewer/light.h"

class Scene : protected QOpenGLFunctions
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
    //
    QVector3D getCameraPosition()           { return camera.getPosition(); }


    // transform
    void setTransformTranslation(const QVector3D &translation);
    void setTransformScale(float scale);
    void setTransformRotation(float xRot, float yRot);
    // left handed
    // relative to rotations
    QVector3D forwardTransform() const      { return transform.forward(); }
    QVector3D upTransform() const           { return transform.up(); }
    QVector3D rightTransform() const        { return transform.right(); }


    void initializeSceneOpenGLFunctions();
    void changeProjection(int width, int height);
    bool isReady();


    // transformation matrice getters
    const QMatrix4x4 &getModelToWorldMatrix();
    const QMatrix4x4 &getWorldToCameraMatrix();
    const QMatrix4x4 &getCameraToViewMatrix();


    // add texture to program
    void addDiffuseMap(QImage &diffuseMap, QOpenGLShaderProgram &program);
    void addDisplacementMap(QImage &displacementMap, QOpenGLShaderProgram &program);

    // getters for texture
    QImage &getDiffuse()        { return diffuse; }
    QImage &getDisplacement()   { return displacement; }


private:
    // transformation matrice
    Camera camera;
    Transform transform;
    QMatrix4x4 projection;

    // set to true when all needed maps are here
    bool ready = false;
    bool checkForReady();

    Light light;


    // Textures
    QImage diffuse;
    QImage displacement;

    // flags for textures
    bool diffuseMapStored       = false;
    bool displacementMapStored  = false;
};

static const Vertex vertices[] {
    // front
    Vertex(-0.5f,  -0.5f,  0.5f, -1.0f, -1.0f, 1.0f ),
    Vertex(0.5f,  -0.5f,  0.5f, 1.0f, -1.0f, 1.0f),
    Vertex(-0.5f,  0.5f,  0.5f, -1.0f, 1.0f, 1.0f),
    Vertex( 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f ),
    // back
    Vertex(0.5f,  -0.5f,  -0.5f, 1.0f, -1.0f, -1.0f),
    Vertex(-0.5f,  -0.5f,  -0.5f, -1.0f, -1.0f, -1.0f),
    Vertex(0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -1.0f),
    Vertex(-0.5f,  0.5f,  -0.5f, -1.0f, 1.0f, -1.0f),
    // top
    Vertex(-0.5f, 0.5f,  0.5f, -1.0f, 1.0f, 1.0f),
    Vertex(0.5f, 0.5f,  0.5f, 1.0f, 1.0f, 1.0f),
    Vertex(-0.5f, 0.5f,  -0.5f, -1.0f, 1.0f, -1.0f),
    Vertex(0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -1.0f),
    // bot
    Vertex(0.5f,  -0.5f,  0.5f, 1.0f, -1.0f, 1.0f),
    Vertex(-0.5f,  -0.5f,  0.5f, -1.0f, -1.0f, 1.0f),
    Vertex(0.5f,  -0.5f,  -0.5f, 1.0f, -1.0f, -1.0f),
    Vertex(-0.5f,  -0.5f,  -0.5f, -1.0f, -1.0f, -1.0f),
    // left
    Vertex(-0.5f,  -0.5f,  -0.5f, -1.0f, -1.0f, -1.0f),
    Vertex(-0.5f,  -0.5f,  0.5f, -1.0f, -1.0f, 1.0f),
    Vertex(-0.5f,  0.5f,  -0.5f, -1.0f, 1.0f, -1.0f),
    Vertex(-0.5f,  0.5f,  0.5f, -1.0f, 1.0f, 1.0f),
    // right
    Vertex(0.5f,  -0.5f,  0.5f, 1.0f, -1.0f, 1.0f),
    Vertex(0.5f,  -0.5f,  -0.5f, 1.0f, -1.0f, -1.0f),
    Vertex(0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f),
    Vertex(0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -1.0f)
};


#endif // SCENE_H
