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

void Dot::rotateY(int degree)
{
    GLfloat radians = degree * M_PI / 180;
    GLfloat nX = x * qCos(radians) + y * 0 + z * qSin(radians);
    GLfloat nY = x * 0 + y * 1 + z * 0;
    GLfloat nZ = x * (-qSin(radians)) + y * 0 + z * qCos(radians);
    x = nX;
    y = nY;
    z = nZ;
}

void Dot::rotateX(int degree)
{
    GLfloat radians = degree * M_PI / 180;
    GLfloat nX = x * 1 + y * 0 + z * 0;
    GLfloat nY = x * 0 + y * qCos(radians) + z * (-qSin(radians));
    GLfloat nZ = x * 0 + y * qSin(radians) + z * qCos(radians);
    x = nX;
    y = nY;
    z = nZ;
}

void Dot::rotateZ(int degree)
{
    GLfloat radians = degree * M_PI / 180;
    GLfloat nX = x * qCos(radians) + y * (-qSin(radians)) + z * 0;
    GLfloat nY = x * qSin(radians) + y * qCos(radians) + z * 0;
    GLfloat nZ = x * 0 + y * 0 + z * 1;
    x = nX;
    y = nY;
    z = nZ;
}

void Dot::resize(Dot *A, bool plus, GLfloat increase)
{
    Dot *AB = new Dot(A->getDotX() - this->getDotX(), A->getDotY() - this->getDotY(), A->getDotZ() - this->getDotZ());
    GLfloat distance = qSqrt(qPow(AB->getDotX(), 2) + qPow(AB->getDotY(), 2) + qPow(AB->getDotZ(), 2));
    GLfloat factor = distance;
    if(plus){
        factor = (distance + increase) / distance;
    }
    else{
        factor = (distance - increase) / distance;
    }
    GLfloat ABx = factor * AB->getDotX();
    GLfloat ABy = factor * AB->getDotY();
    GLfloat ABz = factor * AB->getDotZ();
    Dot *ABShtrih =  new Dot(ABx, ABy, ABz);
    this->x = A->x - ABShtrih->x;
    this->y = A->y - ABShtrih->y;
    this->z = A->z - ABShtrih->z;

}

