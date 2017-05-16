#ifndef POLYGON_H
#define POLYGON_H

#include <QList>
#include "dot.h"


class Polygon
{
    QList <Dot*> vertices;
    QList <float> PolygonColors;
public:
    Polygon();
    Polygon(QList <Dot*> input);
    Polygon(Dot *point1, Dot *point2, Dot *point3, Dot *point4);
    void drawPolygon();
    void reset(Dot *point1, Dot *point2, Dot *point3, Dot *point4);
    void setColors(QList <float> colors);
};

#endif // POLYGON_H
