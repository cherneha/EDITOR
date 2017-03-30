#include "theglwidget.h"

void TheGLWidget::addPrism(Prism *toAdd)
{

    this->currentPrisms.push_back(toAdd);
    update();
}

void TheGLWidget::addNewCone(double x, double y, double z, double t, double b, double heights)
{
    Dot *centralDot = new Dot(x, y, z);
    CuttedCone *toPaint = new CuttedCone(centralDot, b, t, heights);
    this->currentCones.push_back(toPaint);
    update();
}

TheGLWidget::TheGLWidget(QWidget *parent): QOpenGLWidget(parent)
{
    this->mouseClick = false;
    this->colors.push_back(0.5);
    this->colors.push_back(0.0);
    this->colors.push_back(0.5);
    this->colors.push_back(1.0);
}
void TheGLWidget::initializeGL()
{
    this->setScreenSizes(613.0, 477.0, 500.0);
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

    glRotatef (20.0, 1.0, 0.0, 0.0);
    glRotatef (5.0, 0.0, 1.0, 0.0);
qDebug() << "i am in paintGL";
    this->drawAxes();
    this->drawFigures();
}
void TheGLWidget::drawFigures()
{
        glColor4f(0.5f, 0.5f, 0.0f, 1.0f);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        int j = 0;
        for(int i = 0; i < currentCones.size(); i++){
            if(this->mouseClick){
            int r = (i & 0x000000FF) >>  0;
            int g = (i & 0x0000FF00) >>  8;
            int b = (i & 0x00FF0000) >> 16;
            this->changeColors(r/255.0, g/255.0, b/255.0, 1.0);
            j = i;
            qDebug() << r/255.0;
            qDebug() << g/255.0;
            qDebug() << b/255.0;
            }
            currentCones[i]->drawCuttedCone(colors);
        }
        for(int i = j + 1; i < currentPrisms.size(); i++){
            if(this->mouseClick){
            int r = (i & 0x000000FF) >>  0;
            int g = (i & 0x0000FF00) >>  8;
            int b = (i & 0x00FF0000) >> 16;
            this->changeColors(r/255.0, g/255.0, b/255.0, 1.0);
            }
            currentPrisms[i - j - 1]->DrawPrism(colors);
        }
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

void TheGLWidget::mousePressEvent(QMouseEvent *event)
{

    this->mouseClick = true;
    emit changeLabel(1);
    this->repaint();

double x = (event->x());
double y =(613.0 - event->y());
qDebug() << x << " #### " << y;

    glFlush();
    glFinish();
    GLenum err;
    while ( ( err = glGetError() ) != GL_NO_ERROR) {
        qDebug() << "error = " << err;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    double data[4];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, data);

    int d1 = data[0] + data[1] * 255 + data[2] * 255 * 255;

    while ( ( err = glGetError() ) != GL_NO_ERROR) {
        qDebug() << "error = " << err;
    }

    qDebug() << "data = " << data[0] <<", " << data[1] << ", " << data[2];

    this->mouseClick = false;
    this->repaint();
}


void TheGLWidget::changeColors(double r, double g, double b, double alpha)
{
    this->colors[0] = r;
    this->colors[1] = g;
    this->colors[2] = b;
    this->colors[3] = alpha;
}


