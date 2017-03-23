#include "window.h"
#include <QDebug>
#include <QString>
#include <QMouseEvent>
#include "src_gui/mainwindow.h"


// Create a cube
Vertex sg_vertexes[] = {
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
    transform.translate(0.0f, 0.0f, -5.0f);
    transform.scale(2.0f);
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
    light.countTangents(sg_vertexes);
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
        m_vertex.create();
        m_vertex.bind();
        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

        // Create Vertex Array Object
        vao.create();
        vao.bind();

        program->enableAttributeArray(0);
        program->enableAttributeArray(1);
        program->enableAttributeArray(2);
        program->enableAttributeArray(3);
        program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
        program->setAttributeBuffer(1, GL_FLOAT, Vertex::texCoordOffset(), Vertex::TexCoordTupleSize, Vertex::stride());
        program->setAttributeBuffer(2, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());
        program->setAttributeBuffer(3, GL_FLOAT, Vertex::tangentOffset(), Vertex::TangentTupleSize, Vertex::stride());
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
        m_vertex.release();
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
        xRot += 180 / 1.5 * (GLfloat)(pe->y() - ptrMousePosition.y())/height();
        yRot += 180 / 1.5 * (GLfloat)(pe->x() - ptrMousePosition.x())/width();
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
    nSca = nSca * 1.1f;
}

void Window::scaleMinus()
{
    nSca = nSca / 1.1f;
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
        if((changedDiffuse || changedNormal || changedSpecular) && (haveNormal))
        {
            texture = new QOpenGLTexture(diffuseMapImage.mirrored());
            texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            texture->setMagnificationFilter(QOpenGLTexture::Linear);

            normalMap = new QOpenGLTexture(normalMapImage.mirrored());
            normalMap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            normalMap->setMagnificationFilter(QOpenGLTexture::Linear);

            specularMap = new QOpenGLTexture(specularMapImage.mirrored());
            specularMap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
            specularMap->setMagnificationFilter(QOpenGLTexture::Linear);


            glActiveTexture(GL_TEXTURE0);
            texture->bind();
            glUniform1i(program->uniformLocation("ourTexture"), 0);

            glActiveTexture(GL_TEXTURE1);
            normalMap->bind();
            glUniform1i(program->uniformLocation("ourNormalMap"), 1);

            glActiveTexture(GL_TEXTURE2);
            specularMap->bind();
            glUniform1i(program->uniformLocation("ourSpecMap"), 0);
            texture->release();
            normalMap->release();
            specularMap->release();
            changedDiffuse = false;
            changedNormal = false;
            changedSpecular = false;
        }
        vao.bind();
        // Sending light direction to shader
        program->setUniformValue(u_lightDir, light.Direction());
        program->setUniformValue(u_modelToWorld, transform.toMatrix());
        glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
        vao.release();
    }
    program->release();
}




void Window::addDiffuse(QImage &difMap)
{
    changedDiffuse = true;
    diffuseMapImage = difMap;
}


void Window::addNormal(QImage &norMap)
{
    changedNormal = true;
    normalMapImage = norMap;
    haveNormal = true;
}


void Window::addSpecular(QImage &specMap)
{
    changedSpecular = true;
    specularMapImage = specMap;
}


void Window::teardownGL()
{
    vao.destroy();
    m_vertex.destroy();
    delete program;
}
