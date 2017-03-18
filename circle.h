#ifndef CIRCLE_H
#define CIRCLE_H

#include <QOpenGLWidget>
#include <QList>
#include "dot.h"
#include "QtMath"
#include <QtDebug>


class Circle
{
    QList <Dot*> dotsInCircle;
public:
    Circle();
    Circle(QList <Dot*> listOfDots);
    void createCircle(int radius, Dot center);
    QList <Dot*> getCircle();
    void paintCircle();
};

#endif // CIRCLE_H
