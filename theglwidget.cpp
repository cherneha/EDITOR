#include "theglwidget.h"

void TheGLWidget::addPrism(Prism *toAdd)
{

    this->currentPrisms.push_back(toAdd);
    qDebug() << "current prisms:" << currentPrisms[currentPrisms.size() - 1];
    paintGL();
}

void TheGLWidget::addNewCone(double x, double y, double z, double t, double b, double heights)
{
    Dot *centralDot = new Dot(x, y, z);
    CuttedCone *toPaint = new CuttedCone(centralDot, b, t, heights);
    this->currentCones.push_back(toPaint);
    qDebug() << "current cones:" << currentCones[currentCones.size() - 1];
    paintGL();
}

TheGLWidget::TheGLWidget(QWidget *parent): QOpenGLWidget(parent)
{}
void TheGLWidget::initializeGL()
{
    this->setScreenSizes(400.0, 400.0, 400.0);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glClearDepth( 1.0f );
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

}

void TheGLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(-xLength/2, -yLength/2, xLength, yLength);
    glOrtho(-xLength/2, xLength/2, -yLength/2, yLength/2, -zLength/2, zLength/2);
}

void TheGLWidget::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef (30.0, 1.0, 0.0, 0.0);
    glRotatef (10.0, 0.0, 1.0, 0.0);
qDebug() << "i am in paintGL";
    this->drawAxes();

    glColor4f(0.5f, 0.5f, 0.0f, 1.0f);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    for(int i = 0; i < currentCones.size(); i++){
        (currentCones[i])->drawCuttedCone();
        qDebug() << "cuttedcones in paintGL";
    }
    for(int i = 0; i < currentPrisms.size(); i++){
        currentPrisms[i]->DrawPrism();
    }
//    glPointSize(1.0);
//    Dot circleCenter(0.0, 50.0, 0.0);
//    Dot circleCenter1(0.0, -50.0, 0.0);
//    Circle circle, circle1;
//    circle.createCircle(60, circleCenter);
//    circle1.createCircle(100, circleCenter1);

//    glColor4f(0.0f, 0.5f, 0.0f, 1.0f);
//    CuttedCone cone(circle, circle1);
//    cone.drawCuttedCone();

//    Dot *p1 = new Dot(130.0, 70.0, 30.0);
//    Dot *p2 = new Dot(130.0, 70.0, -30.0);
//    Dot *p3 = new Dot(180.0, 70.0, -30.0);
//    Dot *p4 = new Dot(180.0, 70.0, 30.0);

//    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
//    Prism prism(p1, p2, p3, p4, 120);
//    prism.DrawPrism();
}

void TheGLWidget::setScreenSizes(GLfloat x, GLfloat y, GLfloat z)
{
    this->xLength = x;
    this->yLength = y;
    this->zLength = z;
}

void TheGLWidget::drawAxes()
{
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glColor4f(0.5f, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex3f(0.0f, -yLength, 0.0f);
    glVertex3f(0.0f, yLength, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-xLength, 0.0f, 0.0f);
    glVertex3f(xLength, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -zLength);
    glVertex3f(0.0f, 0.0f, zLength);
    glEnd();
}

