#include "cuttedcone.h"

CuttedCone::CuttedCone()
{}

CuttedCone::CuttedCone(Dot *center, double radius1, double radius2, double heights)
{
    Circle *b = new Circle(radius1, center);
    qDebug() << "///////////////////////";
    Dot *anotherCenter = new Dot(center->getDotX(), center->getDotY() + heights, center->getDotZ());
    Circle *t = new Circle(radius2, anotherCenter);
    bottom = *b;
    top = *t;
qDebug() << "cone constructor";
qDebug() << "creating";
}

void CuttedCone::setTop(Circle toTop)
{
    this->top = toTop;
}

void CuttedCone::setBottom(Circle toBottom)
{
    this->bottom = toBottom;
}

void CuttedCone::drawCuttedCone()
{\
    this->top.paintCircle();
    this->bottom.paintCircle();

    glBegin(GL_LINES);
    for(int i = 0; i < this->bottom.getCircle().size(); i++){
        glVertex3f((this->bottom.getCircle()).at(i)->getDotX(), (this->bottom.getCircle()).at(i)->getDotY(), (this->bottom.getCircle()).at(i)->getDotZ());
        glVertex3f((this->top.getCircle()).at(i)->getDotX(), (this->top.getCircle()).at(i)->getDotY(), (this->top.getCircle()).at(i)->getDotZ());
    }
    glEnd();
}
