#ifndef DOT_H
#define DOT_H

#include <QOpenGLWidget>


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

};

#endif // DOT_H
