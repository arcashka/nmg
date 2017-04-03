#ifndef WINDOW_H
#define WINDOW_H
#include <QImage>
#include <QMatrix4x4>
#include <QGroupBox>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "src_viewer/scene.h"




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
    void addDisplacement(QImage &displacementMap);
    void addDiffuse(QImage &diffuseMap);
protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent*);
protected slots:
    void update();
private:
    Scene scene;
    Light light;

    float cameraSpeed = 0.1f;
    float rotatingSpeed = 100.0f;

    // Input stuff
    bool pressed;
    QPoint ptrMousePosition;

    // OpenGL State Information
    QOpenGLBuffer bufferForVertices;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram *program;

    GLuint u_lightColor;
    GLuint u_lightAmbI;
    GLuint u_lightDifI;
    GLuint u_lightDir;
    GLuint u_lightSpec;

    GLuint u_modelToWorld;
    GLuint u_worldToCamera;
    GLuint u_cameraToView;

    QOpenGLTexture *diffuseMap;
    QOpenGLTexture *displacementMap;
};

#endif // WINDOW_H
