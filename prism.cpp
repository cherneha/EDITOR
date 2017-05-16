#include "prism.h"

Prism::Prism()
{

}

Prism::Prism(Dot *base1, Dot *base2, Dot *base3, Dot *base4, int h)
{
    this->base.push_back(base1);
    this->base.push_back(base2);
    this->base.push_back(base3);
    this->base.push_back(base4);

    this->PrismColors.push_back(1.0);
    this->PrismColors.push_back(0.0);
    this->PrismColors.push_back(0.0);
    this->PrismColors.push_back(0.5);


    this->heigth = h;
}

void Prism::DrawPrism()
{
    if(base.size() == 4){

        Dot *top1 = new Dot(base[0]->getDotX(), base[0]->getDotY() - heigth, base[0]->getDotZ());
        Dot *top2 = new Dot(base[1]->getDotX(), base[1]->getDotY() - heigth, base[1]->getDotZ());
        Dot *top3 = new Dot(base[2]->getDotX(), base[2]->getDotY() - heigth, base[2]->getDotZ());
        Dot *top4 = new Dot(base[3]->getDotX(), base[3]->getDotY() - heigth, base[3]->getDotZ());

        Polygon edge(this->base);
        edge.setColors(PrismColors);
        edge.drawPolygon();

        edge.reset(base[3], base[0], top1, top4);
        edge.setColors(PrismColors);
        edge.drawPolygon();

        edge.reset(base[2], base[3], top4, top3);
        edge.setColors(PrismColors);
        edge.drawPolygon();

        edge.reset(base[1], base[2], top3, top2);
        edge.setColors(PrismColors);
        edge.drawPolygon();

        edge.reset(top1, top2, top3, top4);
        edge.setColors(PrismColors);
        edge.drawPolygon();

        edge.reset(base[0], base[1], top2, top1);
        edge.setColors(PrismColors);
        edge.drawPolygon();
    }
}

QList<float> Prism::getColors()
{
    return PrismColors;
}

QList<Dot *> Prism::getDots()
{
    return this->base;
}

void Prism::setBase(QList <Dot*> newBase)
{
    this->base = newBase;
}

void Prism::rotateY(int degree)
{
    for(int i = 0; i < base.size(); i++){
        base[i]->rotateY(degree);
    }
}

void Prism::rotateX(int degree)
{
    for(int i = 0; i < base.size(); i++){
        base[i]->rotateX(degree);
    }
}

void Prism::rotateZ(int degree)
{
    for(int i = 0; i < base.size(); i++){
        base[i]->rotateZ(degree);
    }
}

void Prism::setColors(QList<float> colors)
{
    this->PrismColors = colors;
}

Dot *Prism::findLineCenter(Dot *a, Dot *b)
{
    Dot *center = new Dot((a->getDotX() + b->getDotX())/2, (a->getDotY() + b->getDotY())/2, (a->getDotZ() + b->getDotZ())/2);
    return center;
}

void Prism::resize(bool plus)
{
    Dot *center1 = findLineCenter(base[0], base[2]);
    Dot *center2 = findLineCenter(base[1], base[3]);

    GLfloat distance1 = distance(base[0], base[2]);
    GLfloat distance2 = distance(base[1], base[3]);

    base[0]->resize(center1, plus, 1);
    base[2]->resize(center1, plus, 1);

    GLfloat diagon = distance1 * distance(base[0], base[2]) / distance2;

    base[1]->resize(center1, plus, abs(diagon - distance2));
    base[3]->resize(center2, plus, abs(diagon - distance2));

    GLfloat h = distance1 * distance(base[0], base[2]) / this->heigth;
    this->heigth += (h - this->heigth);
}

GLfloat Prism::distance(Dot *a, Dot *b)
{
    return qSqrt(qPow(a->getDotX() - b->getDotX(), 2) + qPow(a->getDotY() - b->getDotY(), 2) + qPow(a->getDotZ() - b->getDotZ(), 2));
}
