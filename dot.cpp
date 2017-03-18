#include "dot.h"

Dot::Dot()
{

}

Dot::Dot(GLfloat xInput, GLfloat yInput, GLfloat zInput)
{
    this->x = xInput;
    this->y = yInput;
    this->z = zInput;
}

GLfloat Dot::getDotX()
{
    return this->x;
}

GLfloat Dot::getDotY()
{
    return this->y;
}

GLfloat Dot::getDotZ()
{
    return this->z;
}

void Dot::setDotX(GLfloat xInput)
{
    this->x = xInput;
}

void Dot::setDotY(GLfloat yInput)
{
    this->y = yInput;
}

void Dot::setDotZ(GLfloat zInput)
{
    this->z = zInput;
}

void Dot::paintDot()
{
    glBegin(GL_POINTS);
    glVertex3f(this->x, this->y, this->z);
    glEnd();
}

