#ifndef DOT_H
#define DOT_H

#include <QOpenGLWidget>
#include "QtMath"
#include <QDebug>

class Dot
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
public:
    Dot();
    Dot(GLfloat xInput, GLfloat yInput, GLfloat zInput);
    GLfloat getDotX();
    GLfloat getDotY();
    GLfloat getDotZ();
    void setDotX(GLfloat xInput);
    void setDotY(GLfloat yInput);
    void setDotZ(GLfloat zInput);
    void paintDot();
    void rotateY(int degree);
    void rotateX(int degree);
    void rotateZ(int degree);
    void resize(Dot *A, bool plus, GLfloat increase);
    Dot *xProj();
    Dot* yProj();
    Dot *zProj();
};

#endif // DOT_H
