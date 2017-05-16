#ifndef CUTTEDCONE_H
#define CUTTEDCONE_H

#include "circle.h"
#include <vector>



class CuttedCone
{
    Circle bottom;
    Circle top;
    double r1;
    double r2;
    double h;
    QList <float> ConesColors;
public:
    CuttedCone();
    CuttedCone(Dot *center, double radius1, double radius2, double heights);
    void setTop(Circle *toTop);
    void setBottom(Circle *toBottom);
    void drawCuttedCone();
    Dot* getBottom();
    Dot* getTop();
    int getRadiusBottom();
    int getRadiusTop();
    QList<float> getColors();
    void changeColors(QList <float> *colors);
    void rotateY(int degree);
    void rotateX(int degree);
    void rotateZ(int degree);
    void resizeCone(bool PlusOrMin);
    GLfloat distance(Dot *a, Dot *b);
};

#endif // CUTTEDCONE_H
