#ifndef PRISM_H
#define PRISM_H
#include "polygon.h"
#include <vector>


class Prism
{
    QList <Dot*> base;
    int heigth;
public:
    Prism();
    Prism(Dot *base1, Dot *base2, Dot *base3, Dot *base4, int h);
    void DrawPrism(QList <double> colors);
};

#endif // PRISM_H
