#include "cuttedcone.h"

CuttedCone::CuttedCone()
{}

CuttedCone::CuttedCone(Circle topInput, Circle bottomInput)
{
    this->top = topInput;
    this->bottom = bottomInput;
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
