#include "window.h"
#include <QDebug>
#include <QString>
#include <QMouseEvent>
#include "src_gui/mainwindow.h"


// Create a colored cube
Vertex sg_vertexes[] = {
    // front
    Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(1.0f, 1.0f), QVector3D( 1.0f, 1.0f, 1.0f ) ),
    Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(0.0f, 1.0f), QVector3D( -1.0f, 1.0f, 1.0f ) ),
    Vertex( QVector3D(-0.5f,  -0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D( -1.0f, -1.0f, 1.0f ) ),
    Vertex( QVector3D(-0.5f,  -0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D( -1.0f, -1.0f, 1.0f ) ),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D( 1.0f, -1.0f, 1.0f ) ),
    Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(1.0f, 1.0f), QVector3D( 1.0f, 1.0f, 1.0f ) ),
    // back
    Vertex( QVector3D(-0.5f,  0.5f,  -0.5f), QVector2D(1.0f, 1.0f), QVector3D( -1.0f, 1.0f, -1.0f ) ),
    Vertex( QVector3D(0.5f,  0.5f,  -0.5f), QVector2D(0.0f, 1.0f), QVector3D( 1.0f, 1.0f, -1.0f ) ),
    Vertex( QVector3D(0.5f,  -0.5f,  -0.5f), QVector2D(0.0f, 0.0f), QVector3D( 1.0f, -1.0f, -1.0f ) ),
    Vertex( QVector3D(0.5f,  -0.5f,  -0.5f), QVector2D(0.0f, 0.0f), QVector3D( 1.0f, -1.0f, -1.0f ) ),
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f), QVector2D(1.0f, 0.0f), QVector3D( -1.0f, -1.0f, -1.0f ) ),
    Vertex( QVector3D(-0.5f,  0.5f,  -0.5f), QVector2D(1.0f, 1.0f), QVector3D( -1.0f, 1.0f, -1.0f ) ),
    // top
    Vertex( QVector3D(0.5f, 0.5f,  -0.5f), QVector2D(1.0f, 1.0f), QVector3D( 1.0f, 1.0f, -1.0f ) ),
    Vertex( QVector3D(-0.5f, 0.5f,  -0.5f), QVector2D(0.0f, 1.0f), QVector3D( -1.0f, 1.0f, -1.0f ) ),
    Vertex( QVector3D(-0.5f, 0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D( -1.0f, 1.0f, 1.0f ) ),
    Vertex( QVector3D(-0.5f, 0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D( -1.0f, 1.0f, 1.0f ) ),
    Vertex( QVector3D(0.5f, 0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D( 1.0f, 1.0f, 1.0f ) ),
    Vertex( QVector3D(0.5f, 0.5f,  -0.5f), QVector2D(1.0f, 1.0f), QVector3D( 1.0f, 1.0f, -1.0f ) ),
    // bot
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f), QVector2D(1.0f, 1.0f), QVector3D( -1.0f, -1.0f, -1.0f ) ),
    Vertex( QVector3D(0.5f,  -0.5f,  -0.5f), QVector2D(0.0f, 1.0f), QVector3D( 1.0f, -1.0f, -1.0f ) ),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D( 1.0f, -1.0f, 1.0f ) ),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D( 1.0f, -1.0f, 1.0f ) ),
    Vertex( QVector3D(-0.5f,  -0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D( -1.0f, -1.0f, 1.0f ) ),
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f), QVector2D(1.0f, 1.0f), QVector3D( -1.0f, -1.0f, -1.0f ) ),
    // left
    Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(1.0f, 1.0f), QVector3D( -1.0f, 1.0f, 1.0f ) ),
    Vertex( QVector3D(-0.5f,  0.5f,  -0.5f), QVector2D(0.0f, 1.0f), QVector3D( -1.0f, 1.0f, -1.0f ) ),
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f), QVector2D(0.0f, 0.0f), QVector3D( -1.0f, -1.0f, -1.0f ) ),
    Vertex( QVector3D(-0.5f,  -0.5f,  -0.5f), QVector2D(0.0f, 0.0f), QVector3D( -1.0f, -1.0f, -1.0f ) ),
    Vertex( QVector3D(-0.5f,  -0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D( -1.0f, -1.0f, 1.0f ) ),
    Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(1.0f, 1.0f), QVector3D( -1.0f, 1.0f, 1.0f ) ),
    // right
    Vertex( QVector3D(0.5f,  0.5f,  -0.5f), QVector2D(1.0f, 1.0f), QVector3D( 1.0f, 1.0f, -1.0f ) ),
    Vertex( QVector3D(0.5f,  0.5f,  0.5f), QVector2D(0.0f, 1.0f), QVector3D( 1.0f, 1.0f, 1.0f ) ),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D( 1.0f, -1.0f, 1.0f ) ),
    Vertex( QVector3D(0.5f,  -0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D( 1.0f, -1.0f, 1.0f ) ),
    Vertex( QVector3D(0.5f,  -0.5f,  -0.5f), QVector2D(1.0f, 0.0f), QVector3D( 1.0f, -1.0f, -1.0f ) ),
    Vertex( QVector3D(0.5f,  0.5f,  -0.5f), QVector2D(1.0f, 1.0f), QVector3D( 1.0f, 1.0f, -1.0f ) ),
};


Window::Window()
{
    m_transform.translate(0.0f, 0.0f, -5.0f);
    m_transform.scale(2.0f);
}

Window::Window(QGroupBox &)
{
    m_transform.translate(0.0f, 0.0f, -5.0f);
    m_transform.scale(2.0f);
}

Window::Window(QGroupBox *)
{

    m_transform.translate(0.0f, 0.0f, -5.0f);
    m_transform.scale(2.0f);
}


Window::~Window()
{
    //makeCurrent();
    teardownGL();
}


void Window::update()
{
  // Update instance information
  //m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

  // Schedule a redraw
    QWidget::update();
}

/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/

void Window::initializeGL()
{
    m_light.countTangents(sg_vertexes);
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    printContextInformation();

    // Set global information
    glEnable(GL_CULL_FACE);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // Application-specific initialization
    {


        // Create Shader (Do not release until VAO is created)
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader.frag");
        m_program->link();
        m_program->bind();

        // Cache Uniform Locations
        u_modelToWorld = m_program->uniformLocation("modelToWorld");
        u_worldToView = m_program->uniformLocation("worldToView");
        u_lightColor = m_program->uniformLocation("light.Color");
        u_lightAmbI = m_program->uniformLocation("light.AmbientIntensity");
        u_lightDifI = m_program->uniformLocation("light.DiffuseIntensity");
        u_lightDir = m_program->uniformLocation("light.Direction");
        u_lightSpec = m_program->uniformLocation("light.SpecPower");

        // Create Buffer (Do not release until VAO is created)
        m_vertex.create();
        m_vertex.bind();
        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

        // Create Vertex Array Object
        m_object.create();
        m_object.bind();

        m_program->enableAttributeArray(0);
        m_program->enableAttributeArray(1);
        m_program->enableAttributeArray(2);
        m_program->enableAttributeArray(3);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::texCoordOffset(), Vertex::TexCoordTupleSize, Vertex::stride());
        m_program->setAttributeBuffer(2, GL_FLOAT, Vertex::normalOffset(), Vertex::NormalTupleSize, Vertex::stride());
        m_program->setAttributeBuffer(3, GL_FLOAT, Vertex::tangentOffset(), Vertex::TangentTupleSize, Vertex::stride());
        glActiveTexture(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE1);
        glActiveTexture(GL_TEXTURE2);
        // Sending light params to shader
        m_program->setUniformValue(u_lightColor, m_light.Color());
        m_program->setUniformValue(u_lightAmbI, m_light.AmbientIntensity());
        m_program->setUniformValue(u_lightDifI, m_light.DiffuseIntensity());
        m_program->setUniformValue(u_lightSpec, m_light.SpecularPower());



        // Release (unbind) all
        m_object.release();
        m_vertex.release();
        m_program->release();
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
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
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
    if((pe->delta())>0) scalePlus();
    else if((pe->delta())<0) scaleMinus();
    QWidget::update();
}

void Window::paintGL()
{
    m_transform.setRotationXY(xRot, yRot);
    m_transform.setScale(nSca);

    // Clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Render using our shader
    m_program->bind();
    m_program->setUniformValue(u_worldToView, m_projection);
    {
        if((changedDiffuse || changedNormal || changedSpecular) && (haveNormal))
        {
            qDebug() << qPrintable(QString("pew"));
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
            glUniform1i(m_program->uniformLocation("ourTexture"), 0);

            glActiveTexture(GL_TEXTURE1);
            normalMap->bind();
            glUniform1i(m_program->uniformLocation("ourNormalMap"), 1);

            glActiveTexture(GL_TEXTURE2);
            specularMap->bind();
            glUniform1i(m_program->uniformLocation("ourSpecMap"), 0);
            texture->release();
            normalMap->release();
            specularMap->release();
            changedDiffuse = false;
            changedNormal = false;
            changedSpecular = false;
        }
        m_object.bind();
        // Sending light direction to shader
        m_program->setUniformValue(u_lightDir, m_light.Direction());
        m_program->setUniformValue(u_modelToWorld, m_transform.toMatrix());
        glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
        m_object.release();
    }
    m_program->release();
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
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
}

/*******************************************************************************
 * Private Helpers
 ******************************************************************************/

void Window::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get Profile Information
    #define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile())
    {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
    #undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
