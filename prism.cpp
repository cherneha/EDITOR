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
        edge.drawPolygon();

        edge.reset(top1, top2, top3, top4);
        edge.drawPolygon();

        edge.reset(base[0], base[1], top2, top1);
        edge.drawPolygon();

        edge.reset(base[3], base[0], top1, top4);
        edge.drawPolygon();

        edge.reset(base[2], base[3], top4, top3);
        edge.drawPolygon();

        edge.reset(base[1], base[2], top3, top2);
        edge.drawPolygon();

    }
}
