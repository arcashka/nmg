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
    diffuseMapStored = true;

    this->diffuseMap = new QOpenGLTexture(diffuseMap.mirrored());
    this->diffuseMap->setMinificationFilter(QOpenGLTexture::Linear);
    this->diffuseMap->setMagnificationFilter(QOpenGLTexture::Linear);

    program.bind();
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(program.uniformLocation("diffuseMap"), 0);
    this->diffuseMap->bind();

    ready = checkForReady();
    program.release();

    this->diffuseMap->release();
}

void Scene::addDisplacementMap(QImage &displacementMap, QOpenGLShaderProgram &program)
{
    displacementMapStored = true;

    // creating
    this->displacementMap = new QOpenGLTexture(displacementMap.mirrored());
    this->displacementMap->setMinificationFilter(QOpenGLTexture::Linear);
    this->displacementMap->setMagnificationFilter(QOpenGLTexture::Linear);

    // add to our program
    program.bind();
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(program.uniformLocation("displacementMap"), 0);
    this->displacementMap->bind();

    ready = checkForReady();
    program.release();

    this->displacementMap->release();
}

bool Scene::checkForReady()
{
    return (diffuseMapStored &&
            displacementMapStored);
}











