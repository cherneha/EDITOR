#ifndef CUTTEDCONE_H
#define CUTTEDCONE_H

#include"circle.h"
#include <vector>



class CuttedCone
{
    Circle bottom;
    Circle top;
    double r1;
    double r2;
public:
    CuttedCone();
    CuttedCone(Dot *center, double radius1, double radius2, double heights);
    void setTop(Circle toTop);
    void setBottom(Circle toBottom);
    void drawCuttedCone(QList <double> colors);
    double getMinX();
    double getMinY();
};

#endif // CUTTEDCONE_H
