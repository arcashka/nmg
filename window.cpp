#include "window.h"
#include <QDebug>
#include <QString>
#include <QMouseEvent>
#include "src_gui/mainwindow.h"
#include "vertex.h"

Vertex vertices[] = {
    // front
    Vertex( QVector3D( 0.5f,  0.5f,  0.5f)),
    Vertex( QVector3D(-0.5f,  0.5f,  0.5f)),
    Vertex( QVector3D(-0.5f,  -0.5f,  0.5f)),
    Vertex( QVector3D(-0.5f,  -0.5f,  0.5f)),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f)),
    Vertex( QVector3D( 0.5f,  0.5f,  0.5f)),
    // back
    Vertex( QVector3D(-0.5f,  0.5f,  -0.5f)),
    Vertex( QVector3D(0.5f,  0.5f,  -0.5f)),
    Vertex( QVector3D(0.5f,  -0.5f,  -0.5f)),
    Vertex( QVector3D(0.5f,  -0.5f,  -0.5f)),
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f)),
    Vertex( QVector3D(-0.5f,  0.5f,  -0.5f)),
    // top
    Vertex( QVector3D(0.5f, 0.5f,  -0.5f)),
    Vertex( QVector3D(-0.5f, 0.5f,  -0.5f)),
    Vertex( QVector3D(-0.5f, 0.5f,  0.5f)),
    Vertex( QVector3D(-0.5f, 0.5f,  0.5f)),
    Vertex( QVector3D(0.5f, 0.5f,  0.5f)),
    Vertex( QVector3D(0.5f, 0.5f,  -0.5f)),
    // bot
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f)),
    Vertex( QVector3D(0.5f,  -0.5f,  -0.5f)),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f)),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f)),
    Vertex( QVector3D(-0.5f,  -0.5f,  0.5f)),
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f)),
    // left
    Vertex( QVector3D(-0.5f,  0.5f,  0.5f)),
    Vertex( QVector3D(-0.5f,  0.5f,  -0.5f)),
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f)),
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f)),
    Vertex( QVector3D(-0.5f,  -0.5f,  0.5f)),
    Vertex( QVector3D(-0.5f,  0.5f,  0.5f)),
    // right
    Vertex( QVector3D(0.5f,  0.5f,  -0.5f)),
    Vertex( QVector3D(0.5f,  0.5f,  0.5f)),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f)),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f)),
    Vertex( QVector3D(0.5f,  -0.5f,  -0.5f)),
    Vertex( QVector3D(0.5f,  0.5f,  -0.5f))
};

Window::Window(QGroupBox *)
{
}

Window::~Window()
{
    teardownGL();
}

void Window::update()
{
    QWidget::update();
}

void Window::initializeGL()
{
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    // Set global information
    glEnable(GL_CULL_FACE);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // Application-specific initialization
    {
        // Create Shader (Do not release until VAO is created)
        program = new QOpenGLShaderProgram();
        program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
        program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
        program->link();
        program->bind();

        // Cache Uniform Locations
        u_modelToWorld = program->uniformLocation("modelToWorld");
        u_worldToView = program->uniformLocation("worldToView");
        u_lightColor = program->uniformLocation("light.Color");
        u_lightAmbI = program->uniformLocation("light.AmbientIntensity");
        u_lightDifI = program->uniformLocation("light.DiffuseIntensity");
        u_lightDir = program->uniformLocation("light.Direction");
        u_lightSpec = program->uniformLocation("light.SpecPower");

        // Create Buffer (Do not release until VAO is created)
        bufferForVertices.create();
        bufferForVertices.bind();
        bufferForVertices.setUsagePattern(QOpenGLBuffer::StaticDraw);
        bufferForVertices.allocate(vertices, sizeof(vertices));

        // Create Vertex Array Object
        vao.create();
        vao.bind();

        program->enableAttributeArray(0);
        program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
        glActiveTexture(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE1);
        glActiveTexture(GL_TEXTURE2);
        // Sending light params to shader
        program->setUniformValue(u_lightColor, light.Color());
        program->setUniformValue(u_lightAmbI, light.AmbientIntensity());
        program->setUniformValue(u_lightDifI, light.DiffuseIntensity());
        program->setUniformValue(u_lightSpec, light.SpecularPower());

        // Release (unbind) all
        vao.release();
        bufferForVertices.release();
        program->release();
    }
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
        scene.setCameraRotation(180 / 1.5 * (GLfloat)(pe->y() - ptrMousePosition.y()) / height(),
                                180 / 1.5 * (GLfloat)(pe->x() - ptrMousePosition.x()) / width());
        ptrMousePosition = pe->pos();
        QWidget::update();
    }
}

void Window::resizeGL(int width, int height)
{
    projection.setToIdentity();
    projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void Window::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
    QWidget::update();
}

void Window::scalePlus()
{
    scene.scaleCameraBy(1.1f);
}

void Window::scaleMinus()
{
    scene.scaleCameraBy(0.9f);
}

void Window::wheelEvent(QWheelEvent *pe)
{
    if((pe->delta()) > 0) scalePlus();
    else if((pe->delta()) < 0) scaleMinus();
    QWidget::update();
}

void Window::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Render using our shader
    program->bind();
    program->setUniformValue(u_worldToView, projection);
    {
        vao.bind();
        program->setUniformValue(u_lightDir, light.Direction());
        program->setUniformValue(u_modelToWorld, scene.toMatrix());
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
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
