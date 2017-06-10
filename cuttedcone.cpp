#include "cuttedcone.h"

CuttedCone::CuttedCone()
{}

CuttedCone::CuttedCone(Dot *center, double radius1, double radius2, double heights)
{
    ConesColors.push_back(0.0);
    ConesColors.push_back(0.0);
    ConesColors.push_back(0.5);
    ConesColors.push_back(0.3);

    Circle *b = new Circle(radius1, center);
    h = heights;
    Dot *anotherCenter = new Dot(center->getDotX(), center->getDotY() + heights, center->getDotZ());
    Circle *t = new Circle(radius2, anotherCenter);
    bottom = *b;
    top = *t;
    r1 = radius1;
    r2 = radius2;
}

void CuttedCone::setTop(Circle *toTop)
{
    this->top = *toTop;
}

void CuttedCone::setBottom(Circle *toBottom)
{
    this->bottom = *toBottom;
}

void CuttedCone::drawCuttedCone()
{\
    glColor4f(ConesColors[0], ConesColors[1], ConesColors[2], ConesColors[3]);
    this->top.paintCircle();
    this->bottom.paintCircle();

    glBegin(GL_LINES);
    for(int i = 0; i < this->bottom.getCircle().size(); i++){
        glVertex3f((this->bottom.getCircle()).at(i)->getDotX(), (this->bottom.getCircle()).at(i)->getDotY(), (this->bottom.getCircle()).at(i)->getDotZ());
        glVertex3f((this->top.getCircle()).at(i)->getDotX(), (this->top.getCircle()).at(i)->getDotY(), (this->top.getCircle()).at(i)->getDotZ());
    }
    glEnd();
}

Dot* CuttedCone::getBottom()
{
    return this->bottom.getCenter();
}

Dot* CuttedCone::getTop()
{
    return this->top.getCenter();
}

int CuttedCone::getRadiusBottom()
{
    return this->r1;
}

int CuttedCone::getRadiusTop()
{
    return this->r2;
}

int CuttedCone::getHeights()
{
    return this->h;
}

QList<float> CuttedCone::getColors()
{
    return ConesColors;
}

void CuttedCone::changeColors(QList<float> *colors)
{
    this->ConesColors = *colors;
}

void CuttedCone::rotateY(int degree)
{
    this->top.rotateDotsY(degree);
    this->bottom.rotateDotsY(degree);

    this->bottom.getCenter()->setDotX( (bottom.getCircle()[bottom.getCircle().size() - 1]->getDotX() - bottom.getCircle()[bottom.getCircle().size()/2]->getDotX())/2);
    this->bottom.getCenter()->setDotY( (bottom.getCircle()[bottom.getCircle().size() - 1]->getDotY() - bottom.getCircle()[bottom.getCircle().size()/2]->getDotY())/2);
    this->bottom.getCenter()->setDotZ( (bottom.getCircle()[bottom.getCircle().size() - 1]->getDotZ() - bottom.getCircle()[bottom.getCircle().size()/2]->getDotZ())/2);

}

void CuttedCone::rotateX(int degree)
{
    this->top.rotateDotsX(degree);
    this->bottom.rotateDotsX(degree);
}

void CuttedCone::rotateZ(int degree)
{
    this->top.rotateDotsZ(degree);
    this->bottom.rotateDotsZ(degree);
}

void CuttedCone::resizeCone(bool PlusOrMinus)
{
    GLfloat h = distance(this->bottom.getCenter(), this->top.getCenter());
    this->bottom.getCenter()->resize(top.getCenter(), PlusOrMinus, 1);
    this->top.getCenter()->resize(bottom.getCenter(), PlusOrMinus, 1);
    GLfloat hNew = distance(this->bottom.getCenter(), this->top.getCenter());

    this->top.rewriteCircle(this->top.getRadius() * (hNew/h));
    this->bottom.rewriteCircle(this->bottom.getRadius() * (hNew/h));

    this->h = hNew;
    this->r1 = this->bottom.getRadius() * (hNew/h);
    this->r2 = this->top.getRadius() * (hNew/h);
}


GLfloat CuttedCone::distance(Dot *a, Dot *b)
{
    return qSqrt(qPow(a->getDotX() - b->getDotX(), 2) + qPow(a->getDotY() - b->getDotY(), 2) + qPow(a->getDotZ() - b->getDotZ(), 2));
}
