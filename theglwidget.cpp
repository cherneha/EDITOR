#include "theglwidget.h"

TheGLWidget::TheGLWidget(QWidget *parent): QOpenGLWidget(parent)
{
    this->dragStartPosition = new QPoint(0, 0);
}

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

void TheGLWidget::initializeGL()
{
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = { 50.0 };
//    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    this->setScreenSizes(613.0, 477.0, 500.0);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glClearDepth( 1.0f );

//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_ALPHA_TEST);

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
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef (20.0, 1.0, 0.0, 0.0);
    glRotatef (5.0, 0.0, 1.0, 0.0);

    this->drawAxes();
    this->drawFigures();
}

void TheGLWidget::mouseMoveEvent(QMouseEvent *event){

    double x = (event->x());
    double y =(613.0 - event->y());
    double changeX = x - dragStartPosition->x();
    double changeY = y - dragStartPosition->y();
    if(!chosenIndices.empty()){
    int chosen = chosenIndices[chosenIndices.size() - 1] - 1;

    dragdrop = true;
    if(chosen < currentCones.size()){
        Dot *center1 = new Dot(currentCones[chosen]->getBottom()->getDotX() + changeX,
                               currentCones[chosen]->getBottom()->getDotY() + changeY,
                               currentCones[chosen]->getBottom()->getDotZ());
        Circle *bottom = new Circle(currentCones[chosen]->getRadiusBottom(), center1);

        Dot *center2 = new Dot(currentCones[chosen]->getTop()->getDotX() + changeX,
                               currentCones[chosen]->getTop()->getDotY() + changeY,
                               currentCones[chosen]->getTop()->getDotZ());
        Circle *top = new Circle(currentCones[chosen]->getRadiusTop(), center2);
        currentCones[chosen]->setBottom(bottom);
        currentCones[chosen]->setTop(top);
        dragStartPosition->setX(x);
        dragStartPosition->setY(y);
    }

    else{
        QList <Dot*> dots = currentPrisms[chosen - currentCones.size()]->getDots();
        for(int i = 0; i < dots.size(); i++){
            dots[i]->setDotX(dots[i]->getDotX() + changeX);
            dots[i]->setDotY(dots[i]->getDotY() + changeY);
        }
        currentPrisms[chosen - currentCones.size()]->setBase(dots);
        dragStartPosition->setX(x);
        dragStartPosition->setY(y);
    }
    this->repaint();
    }
}

void TheGLWidget::mouseReleaseEvent(QMouseEvent *event){
    if(dragdrop){
    chosenIndices.pop_back();
    dragdrop = false;
    }
    qDebug() << "chosen: " << chosenIndices.size();
    emit changeLabel(chosenIndices.size());
}
void TheGLWidget::mouseDoubleClickEvent(QMouseEvent *event){

}

void TheGLWidget::drawFigures()
{
        glClear(GL_STENCIL_BUFFER_BIT);
        glClearStencil(0);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glEnable(GL_STENCIL_TEST);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        int j = 0;
        for(int i = 0; i < currentCones.size(); i++){
            glStencilFunc(GL_ALWAYS, i + 1, -1);
            currentCones[i]->drawCuttedCone();
            j++;
        }

        for(int i = 0; i < currentPrisms.size(); i++){
            glStencilFunc(GL_ALWAYS, i + j + 1, -1);
            currentPrisms[i]->DrawPrism();
        }
        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
}

void TheGLWidget::rotateChosenYAxis(int degree)
{
    for(int i = 0; i < chosenIndices.size(); i++){
        int chosen = chosenIndices[i] - 1;
        if(chosen < currentCones.size()){
            currentCones[chosen]->rotateY(degree);
        }
        else{
            currentPrisms[chosen - currentCones.size()]->rotateY(degree);
        }
    }
    this->repaint();
}

void TheGLWidget::rotateChosenXAxis(int degree)
{
    for(int i = 0; i < chosenIndices.size(); i++){
        int chosen = chosenIndices[i] - 1;
        if(chosen < currentCones.size()){
            currentCones[chosen]->rotateX(degree);
        }
        else{
            currentPrisms[chosen - currentCones.size()]->rotateX(degree);
        }
    }
    this->repaint();
}

void TheGLWidget::rotateChosenZAxis(int degree)
{
    for(int i = 0; i < chosenIndices.size(); i++){
        int chosen = chosenIndices[i] - 1;
        if(chosen < currentCones.size()){
            currentCones[chosen]->rotateZ(degree);
        }
        else{
            currentPrisms[chosen - currentCones.size()]->rotateZ(degree);
        }
    }
    this->repaint();
}


void TheGLWidget::changeSize(bool plus)
{
    for(int i = 0; i < chosenIndices.size(); i++){
        int chosen = chosenIndices[i] - 1;
        if(chosen < currentCones.size()){
            currentCones[chosen]->resizeCone(plus);
        }
        else{
            currentPrisms[chosen - currentCones.size()]->resize(plus);
        }
    }
    this->repaint();
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
    double x = (event->x());
    double y =(613.0 - event->y());

    dragStartPosition->setX(x);
    dragStartPosition->setY(y);

    int data = 0;
    makeCurrent();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_INT, &data);

    qDebug() << "data = " << data;
    if(data == 0) return;
    bool alreadyChosen = false;
    for(int i = 0; i < chosenIndices.size(); i++){
        if(chosenIndices[i] == data){
            alreadyChosen = true;
            chosenIndices.erase(chosenIndices.begin() + i);
            break;
        }
    }
    if(!alreadyChosen){
        chosenIndices.push_back(data);
    }
}


void TheGLWidget::changeColors(QList <float> *colors)
{
    for(int i = 0; i < chosenIndices.size(); i++){
        int chosen = chosenIndices[i] - 1;
        if(chosen < currentCones.size()){
            currentCones[chosen]->changeColors(colors);
        }
        else{
            currentPrisms[chosen - currentCones.size()]->setColors(*colors);
        }
    }
    this->repaint();
}





