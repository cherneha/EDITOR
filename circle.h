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
    Dot *centre;
    int radius;

public:
    int rotX;
    int rotY;
    int rotZ;
    Circle();
    Circle(int radius, Dot *center);
    QList <Dot*> getCircle();
    void paintCircle();
    Dot* getCenter();
    int getRadius();
    void rotateDotsY(int degree);
    void rotateDotsX(int degree);
    void rotateDotsZ(int degree);
    void rewriteCircle(int radius);
};

#endif // CIRCLE_H
