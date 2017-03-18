#include "circle.h"
#include <QList>


Circle::Circle()
{}

Circle::Circle(QList<Dot *> listOfDots)
{
    for(int i = 0; i < listOfDots.size(); i++){
        this->dotsInCircle.push_back(listOfDots[i]);
    }
}

void Circle::createCircle(int radius, Dot center)
{
    for(int i = 0; i < 2000; i++){
        qDebug() << "creating";
        Dot *toAdd = new Dot;
        toAdd->setDotX(center.getDotX() + radius * qCos((2 * M_PI * i) / 2000));
        toAdd->setDotZ(center.getDotZ() + radius * qSin((2 * M_PI * i) / 2000));
        toAdd->setDotY(center.getDotY());
        dotsInCircle.push_back(toAdd);
        //qDebug() << dotsInCircle[i]->getDotX() << "|" << dotsInCircle[i]->getDotY() << "|" << dotsInCircle[i]->getDotZ() << "*";

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




