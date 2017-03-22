#ifndef CUTTEDCONE_H
#define CUTTEDCONE_H

#include"circle.h"



class CuttedCone
{
    Circle bottom;
    Circle top;
public:
    CuttedCone();
    CuttedCone(Dot *center, double radius1, double radius2, double heights);
    void setTop(Circle toTop);
    void setBottom(Circle toBottom);
    void drawCuttedCone();
};

#endif // CUTTEDCONE_H
