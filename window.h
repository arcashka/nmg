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
#include "light.h"
#include "scene.h"



class QOpenGLShaderProgram;

class Window : public QOpenGLWidget,
               protected QOpenGLFunctions
{
    Q_OBJECT

// OpenGL Events
public:
    ~Window();
    Window(QGroupBox*);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void teardownGL();

protected:
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent* pe);
protected slots:
    void update();

private:
    Scene scene;

    bool pressed;
    QPoint ptrMousePosition;
    void scalePlus();
    void scaleMinus();

    // OpenGL State Information
    QOpenGLBuffer bufferForVertices;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram *program;

    // Textures
    QOpenGLTexture *texture;
    QOpenGLTexture *normalMap;
    QOpenGLTexture *specularMap;

    GLuint u_lightColor;
    GLuint u_lightAmbI;
    GLuint u_lightDifI;
    GLuint u_lightDir;
    GLuint u_lightSpec;

    GLuint u_modelToWorld;
    GLuint u_worldToView;
    GLuint u_texture;
    QMatrix4x4 projection;
    Light light;
};

#endif // WINDOW_H
