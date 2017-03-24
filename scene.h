#ifndef SCENE_H
#define SCENE_H
#include <QQuaternion>
#include <QMatrix4x4>
#include <QImage>

class Scene
{
public:
    Scene();

    // object transforms
    void setObjRotation(float rotX, float rotY);

    // camera transforms
    void scaleCameraBy(float factor);
    void setCameraRotation(float rotX, float rotY);
    void setCameraLocation(QVector3D newLocation);

    QMatrix4x4& toMatrix();

    void addDiffuse(QImage& difMap);
    void addNormal(QImage& norMap);
    void addSpecular(QImage& specMap);
private:
    bool dirty;

    QMatrix4x4 transform;

    // probably won't be used
    QVector3D scaleCamera;
    QVector3D translationCamera;
    QQuaternion rotationCamera;
};

#endif // SCENE_H
