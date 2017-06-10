#include "circle.h"
#include <QList>


Circle::Circle()
{}


Circle::Circle(int radius, Dot* center)
{
    this->centre = center;
    this->radius = radius;
    for(int i = 0; i < 2000; i++){
        Dot *toAdd = new Dot;
        toAdd->setDotX(center->getDotX() + radius * qCos((2 * M_PI * i) / 2000));
        toAdd->setDotZ(center->getDotZ() + radius * qSin((2 * M_PI * i) / 2000));
        toAdd->setDotY(center->getDotY());
        dotsInCircle.push_back(toAdd);
    }
}

QList <Dot*> Circle::getCircle()
{
    return this->dotsInCircle;
}

void Circle::paintCircle()
{
    for(int i = 0; i < dotsInCircle.size(); i++){
        dotsInCircle[i]->paintDot();
        }

    int size = dotsInCircle.size();

    // зарисовка окружности

    glBegin(GL_LINES);
    for(int i = 0; i  < size/2; i++){
        glVertex3f(dotsInCircle[i]->getDotX(), dotsInCircle[i]->getDotY(), dotsInCircle[i]->getDotZ());
        glVertex3f(dotsInCircle[size - 1 - i]->getDotX(), dotsInCircle[size - i - 1]->getDotY(), dotsInCircle[size - i - 1]->getDotZ());
    }
    glEnd();
}

Dot *Circle::getCenter()
{
    return this->centre;
}

int Circle::getRadius()
{
    return this->radius;
}

void Circle::rotateDotsY(int degree)
{
    for(int i = 0; i < this->dotsInCircle.size(); i++){
        dotsInCircle[i]->rotateY(degree);
    }
}

void Circle::rotateDotsX(int degree)
{
    for(int i = 0; i < this->dotsInCircle.size(); i++){
        dotsInCircle[i]->rotateX(degree);
    }

}

void Circle::rotateDotsZ(int degree)
{
    for(int i = 0; i < this->dotsInCircle.size(); i++){
        dotsInCircle[i]->rotateZ(degree);
    }
}

void Circle::rewriteCircle(int radius)
{
    this->radius = radius;
    this->dotsInCircle.clear();
    for(int i = 0; i < 2000; i++){
        Dot *toAdd = new Dot;
        toAdd->setDotX(this->centre->getDotX() + radius * qCos((2 * M_PI * i) / 2000));
        toAdd->setDotZ(this->centre->getDotZ() + radius * qSin((2 * M_PI * i) / 2000));
        toAdd->setDotY(this->centre->getDotY());
        dotsInCircle.push_back(toAdd);
    }
}




