#ifndef KEYS_H
#define KEYS_H

#include <QWidget>
#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtDebug>

class Keys : public QWidget
{
    Q_OBJECT
public:
    explicit Keys(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
};

#endif // KEYS_H
