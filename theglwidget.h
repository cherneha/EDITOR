#ifndef THEGLWIDGET_H
#define THEGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtDebug>
#include <QKeyEvent>
#include "dot.h"
#include "circle.h"
#include "cuttedcone.h"
#include "polygon.h"
#include "prism.h"



class TheGLWidget : public QOpenGLWidget
{
    Q_OBJECT
    GLfloat xLength;
    GLfloat yLength;
    GLfloat zLength;
public:
    explicit TheGLWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void move(QKeyEvent *pressedKey);
    void setScreenSizes(GLfloat x, GLfloat y, GLfloat z);
    void drawAxes();
};

#endif // THEGLWIDGET_H
