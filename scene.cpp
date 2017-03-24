#include "scene.h"

Scene::Scene()
{
    transform.translate(0.0f, 0.0f, -5.0f);
    transform.scale(2.0f);
}


void Scene::scaleCameraBy(float factor)
{
    dirty = true;
    scaleCamera = scaleCamera * factor;
}

void Scene::setCameraRotation(float rotX, float rotY)
{
    dirty = true;
    rotationCamera = QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), rotX) *
                     QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), rotY);
}

void Scene::setCameraLocation(QVector3D newLocation)
{
    dirty = true;
    translationCamera = newLocation;
}

//void Scene::setObjectRotation(float rotX, float rotY)
//{
//    dirty = true;
//    rotationCamera = QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), rotX) *
//                     QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), rotY);
//}

QMatrix4x4& Scene::toMatrix()
{
    if(dirty)
    {
        dirty = false;
        transform.setToIdentity();
        transform.translate(translationCamera);
        transform.rotate(rotationCamera);
        transform.scale(scaleCamera);
    }
    return transform;
}

//void Scene::setCameraScale(float factor)
//{
//    dirty = true;
//    transform.scale(factor);
//}

//void Scene::setCameraRotation(float rotX, float rotY)
//{
//    dirty = true;
//    transform.rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), rotX) *
//                     QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), rotY));
//}

//void Scene::setCameraLocation(QVector3D newLocation)
//{
//    dirty = true;
//    transform.translate(newLocation);
//}

//void Scene::setObjectRotation(float rotX, float rotY)
//{
//    dirty = true;
//    transform.rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), rotX) *
//                     QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), rotY));
//}

//QMatrix4x4& toMatrix()
//{
//    return transform;
//}
