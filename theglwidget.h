#ifndef THEGLWIDGET_H
#define THEGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtDebug>
#include <QKeyEvent>
#include <QList>
#include "dot.h"
#include "circle.h"
#include "cuttedcone.h"
#include "polygon.h"
#include "prism.h"
#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include "mainwindow.h"
#include <QMouseEvent>
#include <vector>
#include <string>
#include <QDrag>
#include "QtMath"
#include <QPoint>


class TheGLWidget : public QOpenGLWidget
{
    Q_OBJECT
    GLfloat xLength;
    GLfloat yLength;
    GLfloat zLength;
public:
    friend class MainWindow;
    QList <Prism*> currentPrisms;
    QList <CuttedCone*> currentCones;
    QList <int> chosenIndices;
    QPoint *dragStartPosition;
    bool dragdrop = false;

    explicit TheGLWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mouseDoubleClickEvent(QMouseEvent *event);
    void drawFigures();
    void move(QKeyEvent *pressedKey);
    void setScreenSizes(GLfloat x, GLfloat y, GLfloat z);
    void drawAxes();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void changeColors(QList <float> *colors);
public slots:
    void addPrism(Prism *toAdd);
    void addNewCone(double x, double y, double z, double t, double b,  double heights);
    void rotateChosenYAxis(int degree);
    void rotateChosenXAxis(int degree);
    void rotateChosenZAxis(int degree);
    void changeSize(bool plus);
signals:
    void changeLabel(int index);
};

#endif // THEGLWIDGET_H
