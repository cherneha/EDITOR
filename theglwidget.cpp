#include "theglwidget.h"

TheGLWidget::TheGLWidget(QWidget *parent): QOpenGLWidget(parent)
{
    this->dragStartPosition = new QPoint(0, 0);
}

void TheGLWidget::addPrism(Dot *dot1, Dot *dot2, Dot *dot3, Dot *dot4, int heights)
{
    Prism *toAdd = new Prism(dot1, dot2, dot3, dot4, heights);
    this->currentPrisms.push_back(toAdd);
    this->insertToDatabaseP(toAdd, currentPrisms.size() - 1);
    update();
}

void TheGLWidget::addNewCone(double x, double y, double z, double t, double b, double heights)
{
    Dot *centralDot = new Dot(x, y, z);
    CuttedCone *toPaint = new CuttedCone(centralDot, b, t, heights);
    this->currentCones.push_back(toPaint);
    this->insertToDatabase(toPaint, currentCones.size() - 1);
    update();
}

void TheGLWidget::initializeGL()
{
    this->setScreenSizes(613.0, 477.0, 500.0);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glClearDepth( 1.0f );

    newDatabase();

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
        int chosen = chosenIndices[chosenIndices.size() - 1] - 1;
        if(chosen < currentCones.size()){
            updateDatabase(currentCones[chosen], chosen);
        }
        else{
            chosen = chosen - currentCones.size();
            updateDatabaseP(currentPrisms[chosen], chosen);
        }
    chosenIndices.pop_back();
    dragdrop = false;
    }
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
            updateDatabase(currentCones[chosen], chosen);
        }
        else{
            currentPrisms[chosen - currentCones.size()]->rotateY(degree);
            updateDatabaseP(currentPrisms[chosen - currentCones.size()], chosen - currentCones.size());
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
            updateDatabase(currentCones[chosen], chosen);
        }
        else{
            currentPrisms[chosen - currentCones.size()]->rotateX(degree);
            updateDatabaseP(currentPrisms[chosen - currentCones.size()], chosen - currentCones.size());
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
            updateDatabase(currentCones[chosen], chosen);
        }
        else{
            currentPrisms[chosen - currentCones.size()]->rotateZ(degree);
            updateDatabaseP(currentPrisms[chosen - currentCones.size()], chosen - currentCones.size());
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
            updateDatabase(currentCones[chosen], chosen);
        }
        else{
            currentPrisms[chosen - currentCones.size()]->resize(plus);
            updateDatabaseP(currentPrisms[chosen - currentCones.size()], chosen - currentCones.size());
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

void TheGLWidget::newDatabase()
{
    QDateTime current = QDateTime::currentDateTime();
    QString currentDate = "/home/stasey/" + current.toString() + ".sqlite";

    // declaring database

        QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
        db = currentDate;
        DB.setDatabaseName(currentDate);

        QSqlQuery queryCones(db);
        QSqlQuery queryPrisms(db);

    if (!DB.open())
       {
          qDebug() << "Error: connection with database fail";
       }
       else
       {
          qDebug() << "Database: connection ok";
       }

        QString str = "CREATE TABLE Cones("
                   "id, "
                   "r1, "
                   "r2, "
                   "heights,"
                   "dotX,"
                   "dotY,"
                   "dotZ"
                   ");";

        if(!queryCones.exec(str)){
            qDebug() << "query Create Cones fails";
        }
        str = "CREATE TABLE Prism("
                "dot1X, dot1Y, dot1Z,"
                "dot2X, dot2Y, dot2Z,"
                "dot3X, dot3Y, dot3Z,"
                "dot4X, dot4Y, dot4Z, id, heights);";


        if(!queryPrisms.exec(str)){
            qDebug() << "query Create Prisms fails: " << queryPrisms.lastError();
        }
}

void TheGLWidget::insertToDatabase(CuttedCone *toAdd, int index)
{
    QSqlQuery insQuery;

    if(!insQuery.prepare("INSERT INTO cones(id, r1, r2, heights, dotX, dotY, dotZ)"
                        "VALUES (:id, :r1, :r2, :heights, :dotX, :dotY, :dotZ)")){
        qDebug() << "prepare fails! " << insQuery.lastError();
    }

    insQuery.bindValue(":id", index);
    insQuery.bindValue(":r1", toAdd->getRadiusBottom());
    insQuery.bindValue(":r2", toAdd->getRadiusTop());
    insQuery.bindValue(":heights", toAdd->getHeights());
    insQuery.bindValue(":dotX", toAdd->getBottom()->getDotX());
    insQuery.bindValue(":dotY", toAdd->getBottom()->getDotY());
    insQuery.bindValue(":dotZ", toAdd->getBottom()->getDotZ());

    if(!insQuery.exec()){
        qDebug() << "oops! " << insQuery.lastError().nativeErrorCode();
    }
}
QSqlDatabase TheGLWidget::DBOpen(){
    QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(db);
    if (!DB.open())
       {
          qDebug() << "insertion Error: connection with database fail";
       }
       else
       {
          qDebug() << "insertion Database: connection ok";
       }
    return DB;
}

void TheGLWidget::insertToDatabaseP(Prism *toAdd, int index)
{
    QSqlQuery insQuery;
    if(!insQuery.prepare("INSERT INTO prism (dot1X, dot1Y, dot1Z, dot2X, dot2Y, dot2Z, "
                         "dot3X, dot3Y, dot3Z, dot4X, dot4Y, dot4Z, id, heights)"
                         "VALUES (:dot1X, :dot1Y, :dot1Z, :dot2X, :dot2Y, :dot2Z, "
                         ":dot3X, :dot3Y, :dot3Z, :dot4X, :dot4Y, :dot4Z, :id, :heights)")){
            qDebug() << "prepare fails! " << insQuery.lastError();
    }

    insQuery.bindValue(":dot1X", toAdd->getDots()[0]->getDotX());
    insQuery.bindValue(":dot1Y", toAdd->getDots()[0]->getDotY());
    insQuery.bindValue(":dot1Z", toAdd->getDots()[0]->getDotZ());

    insQuery.bindValue(":dot2X", toAdd->getDots()[1]->getDotX());
    insQuery.bindValue(":dot2Y", toAdd->getDots()[1]->getDotY());
    insQuery.bindValue(":dot2Z", toAdd->getDots()[1]->getDotZ());

    insQuery.bindValue(":dot3X", toAdd->getDots()[2]->getDotX());
    insQuery.bindValue(":dot3Y", toAdd->getDots()[2]->getDotY());
    insQuery.bindValue(":dot3Z", toAdd->getDots()[2]->getDotZ());

    insQuery.bindValue(":dot4X", toAdd->getDots()[3]->getDotX());
    insQuery.bindValue(":dot4Y", toAdd->getDots()[3]->getDotY());
    insQuery.bindValue(":dot4Z", toAdd->getDots()[3]->getDotZ());
    insQuery.bindValue(":id", index);
    insQuery.bindValue(":heights", toAdd->getHeights());

    if(!insQuery.exec()){
        qDebug() << "oops! " << insQuery.lastError().nativeErrorCode();
    }
}

void TheGLWidget::updateDatabase(CuttedCone *Cone, int index)
{
    QSqlQuery query;
    query.prepare("UPDATE Cones SET r1=:r1N, r2=:r2N, heights=:heightsN, dotX=:dotXN, dotY=:dotYN, dotZ=:dotZN WHERE id=:idN");
    query.bindValue(":r1N", Cone->getRadiusBottom());
    query.bindValue(":r2N", Cone->getRadiusTop());
    query.bindValue(":heightsN", Cone->getHeights());
    query.bindValue(":dotXN", Cone->getBottom()->getDotX());
    query.bindValue(":dotYN", Cone->getBottom()->getDotY());
    query.bindValue(":dotZN", Cone->getBottom()->getDotZ());
    query.bindValue(":idN", index);

    if(!query.exec()){
        qDebug() << "oops! " << query.lastError().nativeErrorCode();
    }

}

void TheGLWidget::updateDatabaseP(Prism *toAdd, int index)
{
    //QSqlDatabase DB = DBOpen();
    QSqlQuery updateQuery;

    updateQuery.prepare("UPDATE Prism SET dot1X=:dot1Xn, dot1Y=:dot1Yn, dot1Z=:dot1Zn,"
                        "dot2X=:dot2Xn, dot2Y=:dot2Yn, dot2Z=:dot2Zn, "
                        "dot3X=:dot3Xn, dot3Y=:dot3Yn, dot3Z=:dot3Zn, "
                        "dot4X=:dot4Xn, dot4Y=:dot4Yn, dot4Z=:dot4Zn, heights=:heightsn WHERE id=:idn");

    updateQuery.bindValue(":dot1Xn", toAdd->getDots()[0]->getDotX());
    updateQuery.bindValue(":dot1Yn", toAdd->getDots()[0]->getDotY());
    updateQuery.bindValue(":dot1Zn", toAdd->getDots()[0]->getDotZ());

    updateQuery.bindValue(":dot2Xn", toAdd->getDots()[1]->getDotX());
    updateQuery.bindValue(":dot2Yn", toAdd->getDots()[1]->getDotY());
    updateQuery.bindValue(":dot2Zn", toAdd->getDots()[1]->getDotZ());

    updateQuery.bindValue(":dot3Xn", toAdd->getDots()[2]->getDotX());
    updateQuery.bindValue(":dot3Yn", toAdd->getDots()[2]->getDotY());
    updateQuery.bindValue(":dot3Zn", toAdd->getDots()[2]->getDotZ());

    updateQuery.bindValue(":dot4Xn", toAdd->getDots()[3]->getDotX());
    updateQuery.bindValue(":dot4Yn", toAdd->getDots()[3]->getDotY());
    updateQuery.bindValue(":dot4Zn", toAdd->getDots()[3]->getDotZ());

    updateQuery.bindValue(":heightsn", toAdd->getHeights());
    updateQuery.bindValue(":idn", index);

    if(!updateQuery.exec()){
        qDebug() << "oops! " << updateQuery.lastError();
    }
}







