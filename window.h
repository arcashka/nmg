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
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent*);
protected slots:
    void update();
private:
    Scene scene;
    float cameraSpeed = 0.01f;
    bool pressed;
    QPoint ptrMousePosition;

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
    GLuint u_worldToCamera;
    GLuint u_cameraToView;
    GLuint u_texture;
    Light light;
};

#endif // WINDOW_H
