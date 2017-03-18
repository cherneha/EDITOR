#include "polygon.h"
#include <QOpenGLWidget>

Polygon::Polygon()
{}

Polygon::Polygon(QList<Dot *> input)
{
    this->vertices = input;
}

Polygon::Polygon(Dot *point1, Dot *point2, Dot *point3, Dot *point4)
{
    this->vertices.push_back(point1);
    this->vertices.push_back(point2);
    this->vertices.push_back(point3);
    this->vertices.push_back(point4);
}

void Polygon::drawPolygon()
{
    glBegin(GL_QUADS);
    for(int i = 0; i < this->vertices.size(); i++){
        glVertex3f(this->vertices[i]->getDotX(), this->vertices[i]->getDotY(), this->vertices[i]->getDotZ());
    }
    glEnd();
}

void Polygon::reset(Dot *point1, Dot *point2, Dot *point3, Dot *point4)
{
    this->vertices.clear();
    this->vertices.push_back(point1);
    this->vertices.push_back(point2);
    this->vertices.push_back(point3);
    this->vertices.push_back(point4);

}

