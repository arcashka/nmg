#include "window.h"
#include <QDebug>
#include <QString>
#include <QMouseEvent>
#include "src_gui/mainwindow.h"

Window::Window(QGroupBox *)
{
}

Window::~Window()
{
    teardownGL();
}

void Window::update()
{
    scene.setTransformRotation(0.1f, 0.1f);

    program->bind();
    program->setUniformValue(u_modelToWorld, scene.getModelToWorldMatrix());
    program->release();
    QWidget::update();
}

void Window::initializeGL()
{
    initializeOpenGLFunctions();
    scene.initializeSceneOpenGLFunctions();
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    glClearColor(0.55f, 0.5f, 0.65f, 1.0f);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Add shaders sourse code
    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
    program->addShaderFromSourceFile(QOpenGLShader::TessellationControl, ":/shaders/shader.tessc");
    program->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, ":/shaders/shader.tesse");
    program->link();
    program->bind();


    // uniform matrices locations
    u_modelToWorld = program->uniformLocation("modelToWorld");
    u_cameraToView = program->uniformLocation("cameraToView");
    u_worldToCamera = program->uniformLocation("worldToCamera");

    // let's make our own depth buffer
    u_cameraPosition = program->uniformLocation("cameraPos");

    // light stuff
    u_lightColor = program->uniformLocation("light.Color");
    u_lightAmbI = program->uniformLocation("light.AmbientIntensity");
    u_lightDifI = program->uniformLocation("light.DiffuseIntensity");
    u_lightDir = program->uniformLocation("light.Direction");
    u_lightSpec = program->uniformLocation("light.SpecPower");

    // Create Buffer for vao
    bufferForVertices.create();
    bufferForVertices.bind();
    bufferForVertices.setUsagePattern(QOpenGLBuffer::StaticDraw);
    bufferForVertices.allocate(vertices, sizeof(vertices));

    // Create Vertex Array Object
    vao.create();
    vao.bind();


    program->setPatchVertexCount(4);


    program->enableAttributeArray(0);
    program->enableAttributeArray(1);
    int position = program->attributeLocation("position");
    int normal = program->attributeLocation("normal");
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 24);
    program->setAttributeBuffer(1, GL_FLOAT, 12, 3, 24);

    // THIS GOTTA BE IN THE PLACE THERE LIGHT STATS ARE CHANGING
    ///////////////////////////////////////////////////////////////
    program->setUniformValue(u_lightColor, light.Color());
    program->setUniformValue(u_lightAmbI, light.AmbientIntensity());
    program->setUniformValue(u_lightDifI, light.DiffuseIntensity());
    program->setUniformValue(u_lightSpec, light.SpecularPower());
    program->setUniformValue(u_lightDir, light.Direction());
    ///////////////////////////////////////////////////////////////


    program->setUniformValue(u_cameraToView, scene.getCameraToViewMatrix());
    program->setUniformValue(u_worldToCamera, scene.getWorldToCameraMatrix());
    program->setUniformValue(u_modelToWorld, scene.getModelToWorldMatrix());

    program->setUniformValue(u_cameraPosition, scene.getCameraPosition());
    vao.release();
    bufferForVertices.release();
    program->release();
}

void Window::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
        scene.translateCameraBy(cameraSpeed, scene.forwardCamera());
    if(event->key() == Qt::Key_S)
        scene.translateCameraBy(-cameraSpeed, scene.forwardCamera());
    if(event->key() == Qt::Key_A)
        scene.translateCameraBy(-cameraSpeed, scene.rightCamera());
    if(event->key() == Qt::Key_D)
        scene.translateCameraBy(cameraSpeed, scene.rightCamera());
    if(event->key() == Qt::Key_Q)
        scene.translateCameraBy(-cameraSpeed, scene.upCamera());
    if(event->key() == Qt::Key_E)
        scene.translateCameraBy(cameraSpeed, scene.upCamera());

    program->bind();
    program->setUniformValue(u_worldToCamera, scene.getWorldToCameraMatrix());
    program->setUniformValue(u_cameraPosition, scene.getCameraPosition());
    program->release();

    QWidget::update();
}

void Window::mousePressEvent(QMouseEvent *pe)
{
    pressed = true;
    ptrMousePosition = pe->pos();
}

void Window::mouseMoveEvent(QMouseEvent *pe)
{
    if(pressed)
    {
        scene.setCameraRotation(
                    rotatingSpeed * (GLfloat)(pe->x() - ptrMousePosition.x()) / width(),
                    scene.upLocalCamera());
        scene.setCameraRotation(
                    rotatingSpeed * (GLfloat)(pe->y() - ptrMousePosition.y()) / height(),
                    scene.rightCamera());
        ptrMousePosition = pe->pos();

        // new camera position and world to camera matrice going to the shader
        program->bind();
        program->setUniformValue(u_worldToCamera, scene.getWorldToCameraMatrix());
        program->setUniformValue(u_cameraPosition, scene.getCameraPosition());
        program->release();

        QWidget::update();
    }
}

void Window::resizeGL(int width, int height)
{
    scene.changeProjection(width, height);
    program->bind();
    program->setUniformValue(u_cameraToView, scene.getCameraToViewMatrix());
    program->release();
    QWidget::update();
}

void Window::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
    QWidget::update();
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_DEPTH_BUFFER_BIT);
    program->bind();
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    if(scene.isReady())
    {
        // diffuse map attaching
        {
            glActiveTexture(GL_TEXTURE0);
            this->diffuseMap->bind();
            glUniform1i(program->uniformLocation("diffuseMap"), 0);
        }
        // displacement map attaching
        {
            glActiveTexture(GL_TEXTURE1);
            this->displacementMap->bind();
            glUniform1i(program->uniformLocation("displacementMap"), 1);
        }
        vao.bind();
        glDrawArrays(GL_PATCHES, 0, sizeof(vertices) / sizeof(vertices[0]));
        this->diffuseMap->release();
        this->displacementMap->release();
        vao.release();
    }
    program->release();
}

void Window::teardownGL()
{
    vao.destroy();
    bufferForVertices.destroy();
    delete program;
}

void Window::addDisplacement(QImage &displacementMap)
{
    scene.addDisplacementMap(displacementMap, *program);
    this->displacementMap = new QOpenGLTexture(scene.getDisplacement().mirrored());
    this->displacementMap->setMinificationFilter(QOpenGLTexture::Linear);
    this->displacementMap->setMagnificationFilter(QOpenGLTexture::Linear);
}

void Window::addDiffuse(QImage &diffuseMap)
{
    scene.addDiffuseMap(diffuseMap, *program);
    this->diffuseMap = new QOpenGLTexture(scene.getDiffuse().mirrored());
    this->diffuseMap->setMinificationFilter(QOpenGLTexture::Linear);
    this->diffuseMap->setMagnificationFilter(QOpenGLTexture::Linear);
}
