#include "scene.h"

Scene::Scene()
{
}

void Scene::setCameraTranslation(const QVector3D &translation)
{
    camera.setTranslation(translation);
}

void Scene::setCameraRotation(float xRot, const QVector3D axis)
{
    camera.setRotation(xRot, axis);
}

void Scene::translateCameraBy(float speed, const QVector3D axis)
{
    camera.translateBy(speed, axis);
}

void Scene::setTransformTranslation(const QVector3D &translation)
{
    transform.setTranslation(translation);
}

void Scene::setTransformScale(float scale)
{
    transform.setScale(scale);
}

void Scene::setTransformRotation(float xRot, float yRot)
{
    transform.setRotation(xRot, yRot);
}

void Scene::initializeSceneOpenGLFunctions()
{
    initializeOpenGLFunctions();
}

void Scene::changeProjection(int width, int height)
{
    projection.setToIdentity();
    projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

bool Scene::isReady()
{
    return ready;
}

const QMatrix4x4 &Scene::getModelToWorldMatrix()
{
    return transform.toMatrix();
}

const QMatrix4x4 &Scene::getWorldToCameraMatrix()
{
    return camera.toMatrix();
}

const QMatrix4x4 &Scene::getCameraToViewMatrix()
{
    return projection;
}

void Scene::addDiffuseMap(QImage &diffuseMap, QOpenGLShaderProgram &program)
{
    diffuse = QImage(diffuseMap);
    diffuseMapStored = true;
    ready = checkForReady();
}

void Scene::addDisplacementMap(QImage &displacementMap, QOpenGLShaderProgram &program)
{
    displacement = QImage(displacementMap);
    displacementMapStored = true;
    ready = checkForReady();
}

bool Scene::checkForReady()
{
    return (diffuseMapStored &&
            displacementMapStored);
}











