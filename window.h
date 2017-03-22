#ifndef WINDOW_H
#define WINDOW_H
#include <QOpenGLWidget>
#include <QImage>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QGroupBox>
#include <QOpenGLTexture>
#include "transform3d.h"
#include "vertex.h"
#include "light.h"



class QOpenGLShaderProgram;

class Window : public QOpenGLWidget,
               protected QOpenGLFunctions
{
    Q_OBJECT

// OpenGL Events
public:
    ~Window();
    Window();
    Window(QGroupBox&);
    Window(QGroupBox*);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void teardownGL();
    void addDiffuse(QImage& difMap);
    void addNormal(QImage& norMap);
    void addSpecular(QImage& specMap);

protected:
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent* pe);
protected slots:
    void update();

private:
    bool haveDiffuse = false;
    bool changedDiffuse = false;

    bool haveSpecular = false;
    bool changedSpecular = false;

    bool haveNormal = false;
    bool changedNormal = false;


    bool pressed = false;

    GLfloat xRot = 0.0f;
    GLfloat yRot = 0.0f;
    GLfloat nSca = 1.0f;
    QPoint ptrMousePosition;

    void scalePlus();
    void scaleMinus();

    // OpenGL State Information
    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram *m_program;

    // Textures
    QOpenGLTexture *texture;
    QOpenGLTexture *normalMap;
    QOpenGLTexture *specularMap;

    QImage diffuseMapImage;
    QImage normalMapImage;
    QImage specularMapImage;

    void bindTextures();

    // Shader Information

    // light
    int u_lightColor;
    int u_lightAmbI;
    int u_lightDifI;
    int u_lightDir;
    int u_lightSpec;

    int u_modelToWorld;
    int u_worldToView;
    int u_texture;
    QMatrix4x4 m_projection;
    Transform3D m_transform;
    light m_light;



    // Private Helpers
    void printContextInformation();
};

#endif // WINDOW_H
