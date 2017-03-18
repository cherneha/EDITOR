#ifndef CUTTEDCONE_H
#define CUTTEDCONE_H

#include"circle.h"



class CuttedCone
{
    Circle bottom;
    Circle top;
public:
    CuttedCone();
    CuttedCone(Circle topInput, Circle bottomInput);
    void setTop(Circle toTop);
    void setBottom(Circle toBottom);
    void drawCuttedCone();
};

#endif // CUTTEDCONE_H
