#ifndef PRISM_H
#define PRISM_H
#include "polygon.h"
#include <vector>
#include "cuttedcone.h"


class Prism
{
    QList <Dot*> base;
    int heigth;
    QList <float> PrismColors;
public:
    Prism();
    Prism(Dot *base1, Dot *base2, Dot *base3, Dot *base4, int h);
    void DrawPrism();
    QList <float> getColors();
    QList <Dot*> getDots();
    void setBase(QList <Dot*>);
    void rotateY(int degree);
    void rotateX(int degree);
    void rotateZ(int degree);
    void setColors(QList <float> colors);
    Dot *findLineCenter(Dot *a, Dot *b);
    void resize(bool plus);
    int getHeights();
    GLfloat distance(Dot *a, Dot *b);
};

#endif // PRISM_H
