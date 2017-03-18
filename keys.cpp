#include "keys.h"

Keys::Keys(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);
}

void Keys::keyPressEvent(QKeyEvent *pressedKey)
{
    if(Qt::Key_Up){
        qDebug() << "key_up" ;
        glRotatef(2.0f, 1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-25.0f, 50.0f, 0.0f);
        glVertex3f(-25.0f, -50.0f, 0.0f);
        glVertex3f(25.0f, -50.0f, 0.0f);
        glVertex3f(25.0f, 50.0f, 0.0f);
        glEnd();
    }
    if( Qt::Key_Down){
        //QDebug::qDebug << "key_down";
        glRotatef(-2.0f, 1.0f, 0.0f, 0.0f);
    }
}
